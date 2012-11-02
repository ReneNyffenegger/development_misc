HBITMAP flickerFreeBitmap;
HDC     flickerFreeMemoryDc;

HBITMAP hOldBitmap;

void InitFlickerFree(HWND hWnd, int windowWidth, int windowHeight) {

  HDC dc = ::GetDC(hWnd);

  flickerFreeBitmap   = ::CreateCompatibleBitmap(dc, windowWidth, windowHeight);
  flickerFreeMemoryDc = ::CreateCompatibleDC(dc);

  hOldBitmap          = (HBITMAP) ::SelectObject(flickerFreeMemoryDc, flickerFreeBitmap);
}

//----------------------- Above: old --- below new, use this (Since 04_Planets.cpp)

class FlickerFreeSupport {

      HBITMAP bitmap;
      HBITMAP oldBitmap;
      HDC     windowDC;
      RECT    windowRect;// = {0, 0, windowWidth, windowHeight};

  public:

  //  Drawing done on memoryDC instead on 'real' DC,
  //  therfore public. Use BitBlt to 'copy' the 
  //  drawn stuff on memoryDC to windowDC
      HDC     memoryDC;


      void Init(HWND hWnd, int width, int height) {
      // HDC dc = ::GetDC(hWnd);
         windowDC   =           ::GetDC(hWnd);

         bitmap     =           ::CreateCompatibleBitmap(windowDC, width, height);
         memoryDC   =           ::CreateCompatibleDC(windowDC);
         hOldBitmap = (HBITMAP) ::SelectObject(memoryDC, bitmap);

         windowRect.top    = 0; 
         windowRect.left   = 0;
         windowRect.bottom = width;
         windowRect.right  = height;

      }

      void StartNewFrame() {
         ::FillRect (memoryDC, &windowRect, (HBRUSH) :: GetStockObject(BLACK_BRUSH));
      }

      void BitBlt() {
         ::BitBlt ( windowDC, 
                    0, 0, windowRect.right/*windowWidth*/, windowRect.bottom/*windowHeight*/,
                    memoryDC,
                    0, 0,
                    SRCCOPY
                    );

      }

};
