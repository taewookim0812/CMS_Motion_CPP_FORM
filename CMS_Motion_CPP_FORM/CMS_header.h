#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

/* ============================================================
                    Inline Functions
============================================================ */

inline double r2d(double rad)
{
    return rad * (180.0 / M_PI);
}

inline double d2r(double deg)
{
    return deg * (M_PI / 180.0);
}

inline std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

/* ============================================================
                    Static Classes
============================================================ */

class OperationMode
{
public:
    static const int RelativeMove = 0x007F;
    static const int AbsoluteMove = 0x003F;

    static const int PositiveHoming = 2;
    static const int NegativeHoming = 1;
    static const int CurrentHoming = 37;
};


class ControlParam
{
public:
    static const int MaxPosition = 100000000;
    static const int MinPosition = -100000000;

    static const int MaxVelocity = 5000;
    static const int MinVelocity = -5000;

    static const double MaxStageAngleDeg;
    static const double MinStageAngleDeg;

    static const uint32_t MaxRepeatCount = 100;
};
const double ControlParam::MaxStageAngleDeg = 15.1;
const double ControlParam::MinStageAngleDeg = -15.1;


class AngularMotion
{
public:
    static const double Radius;             // mm
    static const double ReductionRatio;     // 115 : 1
    static const double ScrewPitch;         // mm
    static const double EncPerRevolution;   // encoder count per revolution

public:
    inline int GetXFromAngle(double deg)
    {
        return (int)(Radius * sin(d2r(deg)));
    }

    inline double GetAngleFromPositionDeg(int pos)
    {
        double stage_angle = asin(
            ((double)pos * (ScrewPitch / (EncPerRevolution * ReductionRatio))) / Radius);
        return r2d(stage_angle);
    }

    inline int GetTargetPositionFromAngleDeg(double deg)
    {
        double x = Radius * sin(d2r(deg));
        return (int)(x / (ScrewPitch / (EncPerRevolution * ReductionRatio)));
    }
};
const double AngularMotion::Radius = 420.0;
const double AngularMotion::ReductionRatio = 115.0;
const double AngularMotion::ScrewPitch = 5.0;
const double AngularMotion::EncPerRevolution = 2000.0;