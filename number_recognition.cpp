//2001223 정용규
//https://www.youtube.com/watch?v=5bQ78DNlzPo
#include <iostream>
using namespace std;
#include "opencv2/opencv.hpp"
using namespace cv;
void mousecallback(int e, int x, int y, int f, void* u) {
    Mat img = *(Mat*)u;
    static Point op;
    Rect r(Point(0, 0), Point(499, 499));
    Rect c(Point(499, 199), Point(699, 299));
    Rect s(Point(499, 0), Point(699, 99));
    Rect l(Point(499, 99), Point(699, 199));
    Rect ex(Point(399, 499), Point(699, 99));
    switch (e) {
    case EVENT_LBUTTONDOWN:
        if (r.contains(Point(x, y))) {
            op = Point(x, y);
        }
        else if (c.contains(Point(x, y))) {
            cout << "cear" << endl;
            img(Rect(Point(2, 2), Point(498, 498))).setTo(255);
        }
        else if (s.contains(Point(x, y))) {
            String s;
            Mat dst;
            cout << "파일 명 입력 :";
            cin >> s;
            resize(img(Rect(Point(2, 2), Point(498, 498))), dst, Size(500, 500), 0, 0);//리사이즈로 500x500사이즈 맞춤
            imwrite(s, dst);
            cout << s << " 저장됨" << endl;
        }
        else if (l.contains(Point(x, y))) {
            String s;
            cout << "파일 명 입력 :";
            cin >> s;
            Mat m = imread(s);
            if (s.empty()) {
                cerr << "이미지 불러오기 실패!" << endl;
                return;
            }
            cout << "iamge 불러옴" << endl;
            resize(m, m, Size(496, 496));
            m.copyTo(img(Rect(Point(2, 2), Point(498, 498))));//사이즈 맞춤
        }
        else if (ex.contains(Point(x, y))) {
            cout << "종료";
            exit(1);
        }
        break;
    case EVENT_MOUSEMOVE:
        if (f & EVENT_FLAG_LBUTTON && r.contains(Point(x, y))) {
            line(img, op, Point(x, y), Scalar(0,0,0), 2);
            op = Point(x, y);
        }
        break;
    default:
        break;
    }
    imshow("img", img);
}
int main(void) {
    Mat img(500, 700, CV_8UC3, Scalar(255,255,255));
    string s[] = { "Save","Load","Clear","Run","Exit" };
    line(img, Point(499, 0), Point(499, 499), 0, 2);
    rectangle(img, Rect(Point(0, 0), Point(img.cols, img.rows)), 0, 2);
    for (int i = 0; i < 5; i++) {
        line(img, Point(499, i * 100), Point(699, i * 100), Scalar(0,0,0), 2);
        Size sizetext = getTextSize(s[i], FONT_HERSHEY_COMPLEX, 2, 3,0);
        putText(img, s[i], Point(499 + (200-sizetext.width)/2, i*100+ (100+sizetext.height)/2), FONT_HERSHEY_COMPLEX, 2, 0, 3);
    }
    imshow("img", img);
    setMouseCallback("img", mousecallback, &img);
    waitKey();
    return 0;
}
