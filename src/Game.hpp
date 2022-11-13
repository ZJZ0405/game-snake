#ifndef GAME_HPP_
#define GAME_HPP_


#include<vector>
#include<opencv2/opencv.hpp>
#include"Game.hpp"
#include<ctime>
#include<random>

struct singlePoint //单个关键点
{
    int x;
    int y;
    int kind;
};

struct multiplePoint //关键点队列
{
    std::vector<int> x;
    std::vector<int> y;
    int kind;
};

class Game
{
private:
    char ch;  //键盘输入

public:

    Game();

protected:
    int getKey(void);

    bool output(const cv::Mat & background) const;

    int random(int start, int end);

    bool change(const singlePoint * center, const singlePoint * single, const cv::Mat & background, const int & LENGTH, const int & WIDE, const int & R) const;

    bool change(const singlePoint * center, const multiplePoint * single, const cv::Mat & background, const int & LENGTH, const int & WIDE, const int & R) const;

    bool showNumber(const cv::Mat & background, const int & LENGTH, const int & WIDE, const int & Num, int kind) const;

};

#endif