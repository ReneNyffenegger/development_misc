const int windowWidth  = 1200;
const int windowHeight = 1200;

class Monitor{
 
  public:
    static const double pixelPerCmHorizontal;// = 1000/26.8;
    static const double pixelPerCmVertical;  // = 1000/26.1;

};

class Viewer {

  public:
    static const double  distanceFromScreenCm;
    static const double  distanceAboveCenterCm;
    static const double  distanceRightOfCenterCm;
    static const double  distanceEyesCm;
    static const point3d left_eye;
    static const point3d right_eye;

};

const double  Viewer::distanceFromScreenCm     = 60;
const double  Viewer::distanceAboveCenterCm    =  0;
const double  Viewer::distanceRightOfCenterCm  =  0;

const double  Viewer::distanceEyesCm = 6.8;
const point3d Viewer::left_eye  = point3d(Viewer::distanceRightOfCenterCm - Viewer::distanceEyesCm/2, Viewer::distanceAboveCenterCm, Viewer::distanceFromScreenCm);
const point3d Viewer::right_eye = point3d(Viewer::distanceRightOfCenterCm + Viewer::distanceEyesCm/2, Viewer::distanceAboveCenterCm, Viewer::distanceFromScreenCm);



class Glasses3D {

  public:
    
    static const COLORREF color_for_right_eye;//   = RGB(255,   0,   0);
    static const COLORREF color_for_left_eye ;//   = RGB(  0,   0, 255);

};

const COLORREF Glasses3D::color_for_right_eye   = RGB(255,   0,   0);
const COLORREF Glasses3D::color_for_left_eye    = RGB(  0,   0, 255); // RGB(  0,   0, 180);

const double Monitor::pixelPerCmHorizontal = 1000/26.8;
const double Monitor::pixelPerCmVertical   = 1000/26.1;

point2d MapPointOntoScreen(point3d const& eye, point3d const& point) {

  point2d point_;

  point_.x = (point.x - eye.x) / (eye.z - point.z) * eye.z + eye.x;
  point_.y = (point.y - eye.y) / (eye.z - point.z) * eye.z + eye.y;

  return point_;
}

int ScreenX(double x/* Todo: , Monitor const& monitor*/) {
  return     (int) (windowWidth /2 + x * Monitor::pixelPerCmVertical  );
}

int ScreenY(double y/*, Monitor const& monitor*/) {
  return     (int) (windowHeight/2 - y * Monitor::pixelPerCmHorizontal);
}

void DrawLine (

     HDC dc,
     matrix_4  const& matrix,
     point3d   const& eye,
     point3d   const& from,
     point3d   const& to

) {


  // Use point3d vector4::operator* (point3d) instead
  // of next 6 statements....
  vector_4 vector_from(from.x, from.y, from.z, 1);
  vector_4 vector_to__(to  .x, to  .y, to  .z, 1);

  vector_4 vector_from_translated = matrix * vector_from;
  vector_4 vector_to___translated = matrix * vector_to__;
 
  point3d from_translated = vector_from_translated.make_point_3d();
  point3d to_translated   = vector_to___translated.make_point_3d();

  point2d from_ = MapPointOntoScreen(eye, from_translated);
  point2d to_   = MapPointOntoScreen(eye, to_translated );

  MoveToEx(
    dc, 
    (int) (windowWidth /2 + from_.x * Monitor::pixelPerCmVertical  ),
    (int) (windowHeight/2 - from_.y * Monitor::pixelPerCmHorizontal),
    0);

  LineTo(
    dc, 
    (int) (windowWidth /2 + to_.x * Monitor::pixelPerCmVertical  ),
    (int) (windowHeight/2 - to_.y * Monitor::pixelPerCmHorizontal));

}


void DrawLine (

     HDC dc,
     matrix_4 const& matrix,
     Viewer   const& viewer,
     point3d  const& from,
     point3d  const& to

) {

  HPEN pen_for_left_eye = CreatePen(PS_SOLID, 1, Glasses3D::color_for_left_eye);
  HPEN pen_old          =(HPEN) SelectObject(dc, pen_for_left_eye);

  DrawLine(dc, matrix, viewer.left_eye, from, to);

  HPEN pen_for_right_eye = CreatePen(PS_SOLID, 1, Glasses3D::color_for_right_eye);
  SelectObject(dc, pen_for_right_eye);

  DrawLine(dc, matrix, viewer.right_eye, from, to);

  SelectObject(dc, pen_old);

  DeleteObject(    pen_for_right_eye);
  DeleteObject(    pen_for_left_eye );

}

void DrawPoint (
   
     HDC dc,
     matrix_4 const& matrix,
     Viewer   const& viewer,
     point3d  const& point,
     double   size = 0

) {


  point3d point_translated = matrix * point;
  
  point2d point_left    = MapPointOntoScreen(viewer.left_eye , point_translated);
  point2d point_right   = MapPointOntoScreen(viewer.right_eye, point_translated);

  if (size == 0) {

     SetPixel(  dc, 
       (int) (windowWidth /2 + point_left.x * Monitor::pixelPerCmVertical  ),
       (int) (windowHeight/2 - point_left.y * Monitor::pixelPerCmHorizontal),
                Glasses3D::color_for_left_eye 
             );
   
     SetPixel(  dc, 
       (int) (windowWidth /2 + point_right.x * Monitor::pixelPerCmVertical  ),
       (int) (windowHeight/2 - point_right.y * Monitor::pixelPerCmHorizontal),
                Glasses3D::color_for_right_eye
             );

  }
  else {

      HPEN pen_for_left_eye = CreatePen(PS_SOLID, 1, Glasses3D::color_for_left_eye);
      HPEN oldPen = (HPEN) SelectObject(dc, pen_for_left_eye);

      // Fill:

      HBRUSH brush_left = CreateSolidBrush(Glasses3D::color_for_left_eye);
      HBRUSH oldBrush = (HBRUSH) SelectObject(dc, brush_left);

      Ellipse(
        dc, 
        ScreenX(point_left.x - size/2.0), 
        ScreenY(point_left.y - size/2.0), 
        ScreenX(point_left.x + size/2.0), 
        ScreenY(point_left.y + size/2.0)
        );

      HPEN pen_for_right_eye = CreatePen(PS_SOLID, 1, Glasses3D::color_for_right_eye);
      /*HPEN oldPen = (HPEN)*/ SelectObject(dc, pen_for_left_eye);
    
      HBRUSH brush_right = CreateSolidBrush(Glasses3D::color_for_right_eye);
      /*oldBrush = (HBRUSH)*/ SelectObject(dc, brush_right);
    
      Ellipse(
        dc, 
        ScreenX(point_right.x - size/2.0), 
        ScreenY(point_right.y - size/2.0), 
        ScreenX(point_right.x + size/2.0), 
        ScreenY(point_right.y + size/2.0)
      );

      SelectObject(dc, oldBrush);
      SelectObject(dc, oldPen);

      DeleteObject(pen_for_right_eye);
      DeleteObject(pen_for_left_eye);
      DeleteObject(brush_left);
      DeleteObject(brush_right);
  }

}
