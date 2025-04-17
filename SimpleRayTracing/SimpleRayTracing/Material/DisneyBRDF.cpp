#include "DisneyBRDF.h"

double DisneyBRDF::fresnel(double cosT) {
    double v = clamp(1 - cosT, 0, 1);
    double v2 = v * v;
    return v2 * v2 * v;
}

double DisneyBRDF::GTR1(double cosT, double a) {
    if (a >= 1) return 1 / Constants::PI;
    double t = (1 + (a * a - 1) * cosT * cosT);
    return (a * a - 1.0f) / (Constants::PI * log(a * a) * t);
}

double DisneyBRDF::GTR2(double cosT, double a) {
    double t = (1 + (a * a - 1) * cosT * cosT);
    return (a * a) / (Constants::PI * t * t);
}

double DisneyBRDF::GGX(double cosT, double a) {
    double a2 = a * a;
    double b = cosT * cosT;
    return 1.0 / (cosT + sqrt(a2 + b - a2 * b));
}

double DisneyBRDF::pdf(Disney* mat, const Hit& hit, const Vec3& wi, const Vec3& wo) {
    Vec3 n = hit.m_normal;

    float specularAlpha = std::max(0.001, mat->m_roughness);
    float clearcoatAlpha = lerp(mat->m_clearcoatGloss, 0.1, 0.001);

    float diffuseRatio = 0.5 * (1.0 - mat->m_metallic);
    float specularRatio = 1.0 - diffuseRatio;

    Vec3 half = (wi + wo).normalize();

    float cosTheta = abs(half.dot(n));
    float pdfGTR2 = GTR2(cosTheta, specularAlpha) * cosTheta;
    float pdfGTR1 = GTR1(cosTheta, clearcoatAlpha) * cosTheta;

    float ratio = 1.0 / (1.0 + mat->m_clearcoat);
    float pdfSpec = lerp(ratio, pdfGTR1, pdfGTR2) / (4.0 * abs(wi.dot(half)));
    float pdfDiff = abs(wi.dot(n)) * (1.0 / Constants::PI);

    return diffuseRatio * pdfDiff + specularRatio * pdfSpec;
}

Vec3 DisneyBRDF::sample_f(Disney* mat, const Hit& hit, const Vec3& wo) {
    double ratiodiffuse = (1 - mat->m_metallic) / 2;
    double p = m_sampler.sample();

    Vec3 w = hit.m_normal;
    Vec3 v = Vec3(0.0034, 1, 0.0071).cross(w);
    v = v.normalize();
    Vec3 u = v.cross(w);

    Vec3 wi;

    if (p < ratiodiffuse) {

        Vec3 p = m_sampler.hemisphere_sample(0);

        wi = u * p.x + v * p.y + w * p.z;
        wi = wi.normalize();
    }
    else {
        float a = std::max(0.001, mat->m_roughness);

        Vec3 p = m_sampler.hemisphere_sample(a * a);

        Vec3 half = u * p.x + v * p.y + w * p.z;
        half = half.normalize();

        wi = half * 2.0 * wo.dot(half) - wo; 
        wi = wi.normalize();
    }

    return wi;
}
//düzenlenmesi lazim daha
Vec3 DisneyBRDF::eval(Disney* mat, const Hit& hit, const Vec3& wi, const Vec3& wo) {
    Vec3 wh = (wi + wo).normalize();

    double ndoth = hit.m_normal.dot(wh);
    double ndotwi = hit.m_normal.dot(wi);
    double ndotwo = hit.m_normal.dot(wo);
    double widoth = wi.dot(wh);

    if (ndotwi <= 0 || ndotwo <= 0)
        return Vec3();

    Vec3 Cdlin = mat->m_baseColor;
    double Cdlum = 0.3 * Cdlin.x + 0.6 * Cdlin.y + 0.1 * Cdlin.z; // luminance approx.

    Vec3 Ctint = Cdlum > 0.0 ? Cdlin / Cdlum : Vec3(1.0); // normalize lum. to isolate hue+sat
    Vec3 Cspec0 = lerp(mat->m_metallic, mat->m_specular * 0.08 * lerp(mat->m_specularTint, Vec3(1.0), Ctint), Cdlin);
    Vec3 Csheen = lerp(mat->m_sheenTint, Vec3(1.0), Ctint);


    //DIFUSE
    double Fd90 = 0.5 + 2 * ndoth * ndoth * mat->m_roughness;
    double Fi = fresnel(ndotwi);
    double Fo = fresnel(ndotwo);

    double Fd = (1 + (Fd90 - 1) * Fi) * (1 + (Fd90 - 1) * Fo);

    double Fss90 = widoth * widoth * mat->m_roughness;
    double Fss = lerp(Fi, 1.0, Fss90) * lerp(Fo, 1.0, Fss90);
    double ss = 1.25 * (Fss * (1.0 / (ndotwi + ndotwo) - 0.5) + 0.5);

    double a = std::max(0.001, mat->m_roughness);
    //specular D
    double Ds = GTR2(ndoth, a);
    //clearcoat D
    double Dc = GTR1(ndoth, lerp(mat->m_clearcoatGloss, 0.1, 0.001));

    //specular G
    double roughg = std::sqrt(mat->m_roughness * 0.5 + 0.5);
    double Gs = GGX(ndotwo, roughg) * GGX(ndotwi, roughg);
    //clearcoat G
    double Gc = GGX(ndotwo, 0.25) * GGX(ndotwi, 0.25);

    //specular F
    double Fh = fresnel(widoth);
    // F = F0 + (1-F0)Fh -> F0 = lepr(Fh,
    Vec3 Fs = lerp(Fh, Cspec0, Vec3(1));
    //clearcoat F
    double Fc = lerp(Fh, 0.04, 1.0);

    // sheen
    Vec3 Fsheen = Fh * mat->m_sheen * Csheen;

    return ((1 / Constants::PI) * lerp(mat->m_subsurface, Fd, ss) * Cdlin + Fsheen) * (1.0 - mat->m_metallic) + Gs * Fs * Ds + 0.25 * mat->m_clearcoat * Gc * Fc * Dc;


}