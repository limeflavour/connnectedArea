#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace std;
using namespace cv;

int main()
{
    Mat srcImage, srcImage_clone, img_thre, labels, stats, centroids, srcImage_gray, srcImage_resize;
    string input = "c";

    while (input != "q")
    {
        string inputName;
        cout << "����ͼƬ����: ";
        cin >> inputName;

        stringstream ss;
        ss << "D:\\��־����\\��������־���Ͼ�-RH\\visualized\\" << inputName << ".visualized.jpg";
        cout << ss.str() << endl;

        srcImage = imread(ss.str());
        if (srcImage.empty())
        {
            cout << "�����ͼƬ����" << endl;
            return -1;
        }

        cvtColor(srcImage, srcImage_gray, COLOR_BGR2GRAY);
        srcImage_clone = srcImage_gray.clone();

        //imshow("srcImage_clone", srcImage_clone);
        //waitKey(0);

        threshold(srcImage_clone, img_thre, 170, 255, THRESH_BINARY_INV);

        Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
        dilate(img_thre, img_thre, element);
        erode(img_thre, img_thre, element);
        dilate(img_thre, img_thre, element);

        string outputNameThre = "D:\\������\\��ֵ������ͨ��\\" + inputName + "��ֵ��" + ".jpg";
        imwrite(outputNameThre, img_thre);
        //imshow("��ֵ������ʴ����", img_thre);
        //waitKey(0);

        int nccomps = connectedComponentsWithStats(img_thre, labels, stats, centroids);
        cout << "stats����Ϊ: " << stats.type() << endl;
        cout << "��⵽�ܵ���ͨ�����Ϊ�� " << nccomps << endl;


        int count = 0;
        double area = 0, width = 0, height = 0;
        for (int i = 0; i < nccomps; i++)
        {
            area = stats.at<int>(i, CC_STAT_AREA);  //why int?
            width = stats.at<int>(i, CC_STAT_WIDTH);
            height = stats.at<int>(i, CC_STAT_HEIGHT);

            if (area < 6400 && area > 400)
            {
                count = count + 1;
            }

        }
        cout << "��⵽������������ͨ�����Ϊ�� " << count << endl;


        for (int i = 0; i < nccomps; i++)
        {
            area = stats.at<int>(i, CC_STAT_AREA);  //why int?
            width = stats.at<int>(i, CC_STAT_WIDTH);
            height = stats.at<int>(i, CC_STAT_HEIGHT);

            if (area < 6400 && area > 400)
            {
                Rect rect(stats.at<int>(i, CC_STAT_LEFT) + 2, stats.at<int>(i, CC_STAT_TOP) + 2, width + 2, height + 2);
                rectangle(srcImage, rect, Vec3b(0, 0, 255), 2);
            }
        }

        string outputNameConn = "D:\\������\\��ֵ������ͨ��\\" + inputName + "��ͨ��" + ".jpg";
        imwrite(outputNameConn, srcImage);

        /*resize(srcImage, srcImage_resize, Size(srcImage.cols / 4, srcImage.rows / 4), 0, 0, CV_INTER_LINEAR);
        imshow("��ͨ��", srcImage_resize);
        waitKey(0);
        destroyAllWindows();*/

        cout << "����q�˳���������������: ";
        cin >> input;
    }
    return 0;
}