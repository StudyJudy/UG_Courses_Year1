#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

char numbers[15] = {'.', '.', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};//为了对齐
char suits[4] = {'D', 'C', 'H', 'S'};

class Poker
{
public:
    int number; //点数（2-14）
    int suit;   //花色（3：黑桃Spade，2：红心Heart，1：梅花Club，0：方块Dianmond）//对应
    // 无参构造函数
    Poker();
    // 有参构造函数
    Poker(int number, int suit);
    // 重载输出运算符，便于格式化输出
    friend ostream &operator<<(ostream &output, const Poker &poker);
};

Poker::Poker(){};

Poker::Poker(int number, int suit)
{
    this->number = number;
    this->suit = suit;
}

// 输出单张扑克牌
ostream &operator<<(ostream &output, const Poker &poker)
{
    output << "(" << numbers[poker.number] << ", " << suits[poker.suit] << ")";
    return output;
}

// 扑克牌比较大小
bool Poker_Compare(const Poker &p1, const Poker &p2)
{
    if (p1.number == p2.number)
    {
        return p1.suit < p2.suit;
    }
    return p1.number < p2.number;
}

class ShowHand
{
    Poker pokers[5];

public:
    ShowHand(Poker *pokers);
    ~ShowHand();
    // 同花顺
    bool Straight_Flush();
    // 四条，四张点数相同的牌
    bool Four_of_a_Kind();
    // 葫芦，三张点数相同和两张点数相同的牌
    bool Full_House();
    // 顺子
    bool Straight();
    // 同花
    bool Flush();
    // 三条，三张点数相同的牌
    bool Three_of_a_Kind();
    // 双对子
    bool Two_Pairs();
    // 一对
    bool One_Pair();

    // 输出牌型和牌组
    void Print();
};

ShowHand::ShowHand(Poker *pokers)
{
    for (int i = 0; i < 5; i++)
    {
        this->pokers[i] = pokers[i];
    }
    // 按牌大小进行排序，方便后面判断牌型
    sort(this->pokers, this->pokers + 5, Poker_Compare);
}

ShowHand::~ShowHand()
{
}

bool ShowHand::Straight_Flush()
{
    return Straight() && Flush();
}

bool ShowHand::Four_of_a_Kind()
{
    // x,x,x,x,y || x,y,y,y,y
    if (pokers[1].number == pokers[2].number && pokers[2].number == pokers[3].number)
    {
        return pokers[0].number == pokers[1].number || pokers[3].number == pokers[4].number;
    }
    return false;
}

bool ShowHand::Full_House()
{
    // x,x,x,z,z || x,x,z,z,z
    if (pokers[0].number == pokers[1].number && pokers[3].number == pokers[4].number)
    {
        return pokers[2].number == pokers[0].number || pokers[2].number == pokers[3].number;
    }
    return false;
}

bool ShowHand::Straight()
{
    // 特殊情况，A 2 3 4 5
    if (pokers[0].number == 2 && pokers[1].number == 3 && pokers[2].number == 4 && pokers[3].number == 5 && pokers[4].number == 14)
    {
        return true;
    }

    // 每张牌依次递增
    for (int i = 0; i < 4; i++)
    {
        if (pokers[i].number + 1 != pokers[i + 1].number)
        {
            return false;
        }
    }
    return true;
}

bool ShowHand::Flush()
{
    for (int i = 0; i < 4; i++)
    {
        if (pokers[i].suit != pokers[i + 1].suit)
        {
            return false;
        }
    }
    return true;
}

bool ShowHand::Three_of_a_Kind()
{
    // 这里需要注意，判断牌型应该从大到小依次判断，三条这里的判断只考虑排除了四条之后的情况。其他也是一样的。具体排序可以参考Print函数。
    // x,x,x,y,z || x,y,y,y,z || x,y,z,z,z
    return (pokers[0].number == pokers[1].number && pokers[1].number == pokers[2].number)
        || (pokers[1].number == pokers[2].number && pokers[2].number == pokers[3].number)
        || (pokers[2].number == pokers[3].number && pokers[3].number == pokers[4].number);
}

bool ShowHand::Two_Pairs()
{
    // 排除了四条和葫芦之后
    // x,x,y,y,z || x,x,y,z,z || x,y,y,z,z
    return (pokers[0].number == pokers[1].number && pokers[2].number == pokers[3].number)
        || (pokers[0].number == pokers[1].number && pokers[3].number == pokers[4].number)
        || (pokers[1].number == pokers[2].number && pokers[3].number == pokers[4].number);
}

bool ShowHand::One_Pair()
{
    // 排除了四条、葫芦、三条、两对之后
    return pokers[0].number == pokers[1].number
        || pokers[1].number == pokers[2].number 
        || pokers[2].number == pokers[3].number 
        || pokers[3].number == pokers[4].number;
}

void ShowHand::Print()
{
    // 判断牌型，按照大小规则依次判断
    if (Straight_Flush())
    {
        cout << "Straight_Flush: ";
    }
    else if (Four_of_a_Kind())
    {
        cout << "Four_of_a_Kind: ";
    }
    else if (Full_House())
    {
        cout << "Full_House: ";
    }
    else if (Straight())
    {
        cout << "Straight: ";
    }
    else if (Flush())
    {
        cout << "Flush: ";
    }
    else if (Three_of_a_Kind())
    {
        cout << "Three_of_a_Kind: ";
    }
    else if (Two_Pairs())
    {
        cout << "Two_Pairs: ";
    }
    else if (One_Pair())
    {
        cout << "One_Pair: ";
    }
    else
    {
        cout << "High_Cards: ";
    }
    // 输出五张牌
    for (int i = 0; i < 5; i++)
    {
        cout << pokers[i] << " ";
    }
    cout << endl;
}

int main()
{
    // 这部分可以用于测试牌型
    // Poker test[5] = {{8, 3}, {8, 2}, {2, 0}, {7, 3}, {7, 1}};
    // ShowHand s(test);
    // s.Print();

    // 先初始化一副牌
    Poker pokerDeck[52];
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            pokerDeck[i * 4 + j] = Poker(i + 2, j);
        }
    }
    // 输出一下
    for (int i = 0; i < 52; i++)
    {
        cout << pokerDeck[i] << " ";
    }
    cout << endl;

    // 利用算法库提供的洗牌算法进行洗牌
    srand(unsigned(time(0)));
    random_shuffle(pokerDeck, pokerDeck + 52);

    // 洗牌后输出
    for (int i = 0; i < 52; i++)
    {
        cout << pokerDeck[i] << " ";
    }
    cout << endl;

    // 前五张牌给第一个玩家
    ShowHand s1(pokerDeck);
    s1.Print();
    // 5-10 牌给第二个玩家
    ShowHand s2(pokerDeck + 5);
    s2.Print();
    // 10-15 牌给第三个玩家
    ShowHand s3(pokerDeck + 10);
    s3.Print();

    return 0;
}