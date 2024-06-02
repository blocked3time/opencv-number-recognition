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
            cout << "���� �� �Է� :";
            cin >> s;
            resize(img(Rect(Point(2, 2), Point(498, 498))), dst, Size(500, 500), 0, 0);//��������� 500x500������ ����
            imwrite(s, dst);
            cout << s << " �����" << endl;
        }
        else if (l.contains(Point(x, y))) {
            String s;
            cout << "���� �� �Է� :";
            cin >> s;
            Mat m = imread(s, IMREAD_GRAYSCALE);
            if (s.empty()) {
                cerr << "�̹��� �ҷ����� ����!" << endl;
                return;
            }
            cout << "iamge �ҷ���" << endl;
            m(Rect(Point(2, 2), Point(498, 498))).copyTo(img(Rect(Point(2, 2), Point(498, 498))));//������ ����
        }
        else if (ex.contains(Point(x, y))) {
            cout << "����";
            exit(1);
        }
        break;
    case EVENT_MOUSEMOVE:
        if (f & EVENT_FLAG_LBUTTON && r.contains(Point(x, y))) {
            line(img, op, Point(x, y), 0, 2);
            op = Point(x, y);
        }
        break;
    default:
        break;
    }
    imshow("img", img);
}
int main(void) {
    Mat img(500, 700, CV_8UC1, 255);
    string s[] = { "Save","Load","Clear","Run","Exit" };
    line(img, Point(499, 0), Point(499, 499), 0, 2);
    rectangle(img, Rect(Point(0, 0), Point(img.cols, img.rows)), 0, 2);
    for (int i = 0; i < 5; i++) {
        line(img, Point(499, i * 100), Point(699, i * 100), 0, 2);
        Size sizetext = getTextSize(s[i], FONT_HERSHEY_COMPLEX, 2, 3, 0);
        putText(img, s[i], Point(499 + (200 - sizetext.width) / 2, i * 100 + (100 + sizetext.height) / 2), FONT_HERSHEY_COMPLEX, 2, 0, 3);
    }
    imshow("img", img);
    setMouseCallback("img", mousecallback, &img);
    waitKey();
    return 0;
}