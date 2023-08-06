#include <SFML/Graphics.hpp>
#include <istream>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <chrono>
#include <map>
#include <algorithm>
#include <ctime>
using namespace std;


class text{
public:

    int width = 800;
    int height = 600;

    void setText(string name,int size,string color){
        sf::Text text;
        sf::Font font;
        font.loadFromFile("files/font.tff");
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(sf::Color::Yellow);
        text.setStyle(sf::Text::Bold);
        sf::FloatRect TitleRect = text.getLocalBounds();
        text.setOrigin(TitleRect.left + TitleRect.width/2.0f,
                        TitleRect.top + TitleRect.height/2.0f);
        text.setPosition(sf::Vector2f(width/2.0f,height/2.0f -150));
    }
};

class tiles{
public:
    
    bool isMine;
    bool rightClicked = false;
    bool notRightClicked = true;
    bool drawFlagTile = true;
    bool didClick = false;
    bool pause = false;
    int xPosition;
    int yPosition;
    int near;
    int flagCount = 0;
    sf::Sprite sprite;

    tiles(int x, int y) {
        xPosition = x;
        yPosition = y;
        near = 0;
    }

    void setTile(sf::RenderWindow &window, int x, int y) {

        this-> xPosition = x;
        this->yPosition = y;
    }

    void drawTile(sf::RenderWindow &window) {
        sf::Texture texture;
        texture.loadFromFile("files/images/tile_hidden.png");
        sf::Sprite sprite(texture);
        sprite.setPosition(xPosition,yPosition);
        window.draw(sprite);
    }

    void drawBomb(sf::RenderWindow &window){
        if (!pause){
            sf::Texture texture;
            texture.loadFromFile("files/images/mine.png");
            sf::Sprite sprite(texture);
            sprite.setPosition(xPosition,yPosition);
            window.draw(sprite);
        }
    }

    void drawClickedTile(sf::RenderWindow &window){
        sf::Texture texture;
        texture.loadFromFile("files/images/tile_revealed.png");
        sf::Sprite sprite(texture);
        sprite.setPosition(xPosition,yPosition);
        window.draw(sprite);
    }

    void drawFlag(sf::RenderWindow &window){
        if (drawFlagTile and !pause) {
            sf::Texture texture;
            texture.loadFromFile("files/images/flag.png");
            sf::Sprite sprite(texture);
            sprite.setPosition(xPosition,yPosition);
            window.draw(sprite);
        }
    }

    void drawFlagReveal(sf::RenderWindow &window){
            sf::Texture texture;
            texture.loadFromFile("files/images/flag.png");
            sf::Sprite sprite(texture);
            sprite.setPosition(xPosition,yPosition);
            window.draw(sprite);

    }

    void drawNear(sf::RenderWindow &window) {
        sf::Texture texture;
        if (!pause) {

            if (near == 1) {
                texture.loadFromFile("files/images/number_1.png");
                sf::Sprite sprite(texture);
                sprite.setPosition(xPosition, yPosition);
                window.draw(sprite);
            } else if (near == 2) {
                texture.loadFromFile("files/images/number_2.png");
                sf::Sprite sprite(texture);
                sprite.setPosition(xPosition, yPosition);
                window.draw(sprite);
            } else if (near == 3) {
                texture.loadFromFile("files/images/number_3.png");
                sf::Sprite sprite(texture);
                sprite.setPosition(xPosition, yPosition);
                window.draw(sprite);
            } else if (near == 4) {
                texture.loadFromFile("files/images/number_4.png");
                sf::Sprite sprite(texture);
                sprite.setPosition(xPosition, yPosition);
                window.draw(sprite);
            } else if (near == 5) {
                texture.loadFromFile("files/images/number_5.png");
                sf::Sprite sprite(texture);
                sprite.setPosition(xPosition, yPosition);
                window.draw(sprite);
            } else if (near == 6) {
                texture.loadFromFile("files/images/number_6.png");
                sf::Sprite sprite(texture);
                sprite.setPosition(xPosition, yPosition);
                window.draw(sprite);
            } else if (near == 7) {
                texture.loadFromFile("files/images/number_7.png");
                sf::Sprite sprite(texture);
                sprite.setPosition(xPosition, yPosition);
                window.draw(sprite);
            } else if (near == 8) {
                texture.loadFromFile("files/images/number_8.png");
                sf::Sprite sprite(texture);
                sprite.setPosition(xPosition, yPosition);
                window.draw(sprite);
            }
        }
    }

};

bool sort_(const pair<string, int> &a,
               const pair<string, int> &b)
{
    return (a.second < b.second);
}

void drawRectangle(float x, float y,sf::RenderWindow &window ) {
    sf::Texture texture;
    texture.loadFromFile("files/images/face_happy.png");
    sf::Sprite sprite(texture);
    sprite.setScale(10000,10000);
    window.draw(sprite);
}

void drawLeaders(int width, int height, int place, float x, float y, string name, string time, sf::RenderWindow &window, sf::Text placeText, sf::Text timeText, sf::Text nameText, sf::Font &font, vector<sf::Text> &outputVector) {

    int yPlus = 30 * place;

    string place_ = to_string(place);
    placeText.setFont(font);
    placeText.setString(place_);
    placeText.setCharacterSize(18);
    placeText.setFillColor(sf::Color::Yellow);
    placeText.setStyle(sf::Text::Bold);
    placeText.setPosition(width/2,height/2 + 85 + yPlus);
    outputVector.push_back(placeText);

    timeText.setFont(font);
    timeText.setString(time);
    timeText.setCharacterSize(18);
    timeText.setFillColor(sf::Color::Yellow);
    timeText.setStyle(sf::Text::Bold);
    timeText.setPosition(width/2+80,height/2 + 85 + yPlus);
    outputVector.push_back(timeText);

    nameText.setFont(font);
    nameText.setString(name);
    nameText.setCharacterSize(18);
    nameText.setFillColor(sf::Color::Yellow);
    nameText.setStyle(sf::Text::Bold);
    nameText.setPosition(width/2+240,height/2 + 85 + yPlus);
    outputVector.push_back(nameText);

}

void drawHappyFaceButton(float x, float y,sf::RenderWindow &window, bool &lost, bool &won) {

    if (lost) {
        sf::Texture texture;
        texture.loadFromFile("files/images/face_lose.png");
        sf::Sprite sprite(texture);
        sprite.setPosition(((x/ 2.0) * 32) - 32, 32 *(y+0.5f));
        window.draw(sprite);
    }

    else if (won) {
        sf::Texture texture;
        texture.loadFromFile("files/images/face_win.png");
        sf::Sprite sprite(texture);
        sprite.setPosition(((x/ 2.0) * 32) - 32, 32 *(y+0.5f));
        window.draw(sprite);

    }

    else {
        sf::Texture texture;
        texture.loadFromFile("files/images/face_happy.png");
        sf::Sprite sprite(texture);
        sprite.setPosition(((x/ 2.0) * 32) - 32, 32 *(y+0.5f));
        window.draw(sprite);
    }
}

void drawDebugButtion(float x, float y, sf::RenderWindow &window) {
    sf::Texture texture;
    texture.loadFromFile("files/images/debug.png");
    sf::Sprite sprite(texture);
    sprite.setPosition((x * 32) - 304, 32 * (y+0.5f));
    window.draw(sprite);
}

void drawPauseButton(float x, float y, sf::RenderWindow &window) {
    sf::Texture texture;
    texture.loadFromFile("files/images/pause.png");
    sf::Sprite sprite(texture);
    sprite.setPosition((x * 32) - 240, 32 * (y+0.5f));
    window.draw(sprite);
}

void drawPlayButton(float x, float y, sf::RenderWindow &window) {
    sf::Texture texture;
    texture.loadFromFile("files/images/play.png");
    sf::Sprite sprite(texture);
    sprite.setPosition((x * 32) - 240, 32 * (y+0.5f));
    window.draw(sprite);
}

void drawLeaderboardButton(float x, float y, sf::RenderWindow &window) {
    sf::Texture texture;
    texture.loadFromFile("files/images/leaderboard.png");
    sf::Sprite sprite(texture);
    sprite.setPosition((x * 32) - 176, 32 * (y+0.5f));
    window.draw(sprite);
}

void drawCounter(int mine_, int height, int width, vector<tiles> tilesVector,sf::Sprite &spriteZero, sf::Sprite &spriteOne, sf::Sprite &spriteTwo, sf::Sprite &spriteThree, sf::Sprite &spriteFour,
                 sf::Sprite &spriteFive, sf::Sprite &spriteSix, sf::Sprite &spriteSeven, sf::Sprite &spriteEight, sf::Sprite &spriteNine, sf::Sprite &spriteMinus, sf::RenderWindow &window) {

    int flagCount = mine_;

    for (int k = 0; k < tilesVector.size(); k++) {
        if(tilesVector.at(k).rightClicked) {
            flagCount -= 1;
        }
        else if (!tilesVector.at(k).notRightClicked) {
            flagCount += 1;
        }
    }
    spriteZero.setPosition(33,32 * (height+.05f)+16);
    window.draw(spriteZero);
    spriteZero.setPosition(54,32 * (height+.05f)+16);
    window.draw(spriteZero);
    spriteZero.setPosition(75,32 * (height+.05f)+16);
    window.draw(spriteZero);

    string flagCount_ = to_string(flagCount);
    unsigned int numbers = flagCount_.length();

    int xPlus = 21 * (3-numbers);




    for (unsigned int i = 0; i < numbers; i++) {
        if (flagCount_[i] == '0') {
            spriteZero.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteZero);
        }
        else if (flagCount_[i] == '1') {
            spriteOne.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteOne);
        }

        else if (flagCount_[i] == '2') {
            spriteTwo.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteTwo);
        }

        else if (flagCount_[i] == '3') {
            spriteThree.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteThree);
        }

        else if (flagCount_[i] == '4') {
            spriteFour.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteFour);
        }

        else if (flagCount_[i] == '5') {
            spriteFive.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteFive);
        }

        else if (flagCount_[i] == '6') {
            spriteSix.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteSix);
        }

        else if (flagCount_[i] == '7') {
            spriteSeven.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteSeven);
        }

        else if (flagCount_[i] == '8') {
            spriteEight.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteEight);
        }

        else if (flagCount_[i] == '9') {
            spriteNine.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteNine);
        }

        else if (flagCount_[i] == '-') {
            spriteMinus.setPosition(33 + xPlus,(32 * (16+.05f)+16));
            window.draw(spriteMinus);
        }

        xPlus += 21;
    }



}

void drawTimer(int mine_, int height, int width, vector<tiles> tilesVector,sf::Sprite &spriteZero, sf::Sprite &spriteOne, sf::Sprite &spriteTwo, sf::Sprite &spriteThree, sf::Sprite &spriteFour,
                 sf::Sprite &spriteFive, sf::Sprite &spriteSix, sf::Sprite &spriteSeven, sf::Sprite &spriteEight, sf::Sprite &spriteNine, sf::Sprite &spriteMinus, sf::RenderWindow &window, chrono::time_point<chrono::system_clock> &start,
               chrono::time_point<chrono::system_clock> &endConstant, chrono::time_point<chrono::system_clock> &startdiff, chrono::time_point<chrono::system_clock> &enddiff, bool play, bool lost, bool won, vector<chrono::duration<double>> &timeVector) {

    chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();

    chrono::duration<double> timeWhenPaused = enddiff - startdiff;

    chrono::duration<double> time = end - start;



    if (won or lost) {
        time = endConstant - start;
        for ( int i = 0; i < timeVector.size(); i++) {
            time = time - timeVector.at(i);
        }
    }

    else if (play) {
        time = end - start;
        for ( int i = 0; i < timeVector.size(); i++) {
            time = time - timeVector.at(i);
        }
    }

    else {
        time = endConstant - start;
        for ( int i = 0; i < timeVector.size(); i++) {
            time = time - timeVector.at(i);
        }
    }


    //minutes
    spriteZero.setPosition((width*32)-97, 32*(height+0.5f )+16);
    window.draw(spriteZero);
    spriteZero.setPosition((width*32)-76, 32*(height+0.5f )+16);
    window.draw(spriteZero);

    //seconds
    spriteZero.setPosition((width*32)-54, 32*(height+0.5f )+16);
    window.draw(spriteZero);
    spriteZero.setPosition((width*32)-33, 32*(height+0.5f )+16);
    window.draw(spriteZero);

        int xPlus = 0;
        int start_ = 33;

        string Time = to_string(chrono::duration_cast<chrono::seconds>(time).count());
        int check = stoi(Time);
        int len = Time.length();
        string min;
        string sec;

        if (check > 60) {
            min = to_string(check / 60);

            if (check % 60 > 9) {
                sec = to_string(check % 60);
            } else {
                sec = "0" + to_string(check % 60);
            }
            Time = min + sec;
        }


        if (check > 60) {

            len = Time.length();

            if (len > 3) {
                start_ = 97;
            } else {
                start_ = 76;
            }

            for (int i = 0; i < len; i++) {

                if (Time[i] == '0') {
                    spriteZero.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteZero);
                } else if (Time[i] == '1') {
                    spriteOne.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteOne);
                } else if (Time[i] == '2') {
                    spriteTwo.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteTwo);
                } else if (Time[i] == '3') {
                    spriteThree.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteThree);
                } else if (Time[i] == '4') {
                    spriteFour.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteFour);
                } else if (Time[i] == '5') {
                    spriteFive.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteFive);
                } else if (Time[i] == '6') {
                    spriteSix.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteSix);
                } else if (Time[i] == '7') {
                    spriteSeven.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteSeven);
                } else if (Time[i] == '8') {
                    spriteEight.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteEight);
                } else if (Time[i] == '9') {
                    spriteNine.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteNine);
                }

                if (i == 0) {
                    xPlus += 22;
                } else {
                    xPlus += 21;
                }

            }


        } else {

            for (int i = 0; i < len; i++) {

                if (len > 1) {
                    start_ = 54;
                }

                if (Time[i] == '0') {
                    spriteZero.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteZero);
                } else if (Time[i] == '1') {
                    spriteOne.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteOne);
                } else if (Time[i] == '2') {
                    spriteTwo.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteTwo);
                } else if (Time[i] == '3') {
                    spriteThree.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteThree);
                } else if (Time[i] == '4') {
                    spriteFour.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteFour);
                } else if (Time[i] == '5') {
                    spriteFive.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteFive);
                } else if (Time[i] == '6') {
                    spriteSix.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteSix);
                } else if (Time[i] == '7') {
                    spriteSeven.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteSeven);
                } else if (Time[i] == '8') {
                    spriteEight.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteEight);
                } else if (Time[i] == '9') {
                    spriteNine.setPosition((width * 32) - start_ + xPlus, 32 * (height + 0.5f) + 16);
                    window.draw(spriteNine);
                }
                xPlus += 21;
            }
        }


}

void revealAllMines(vector<int> board, vector<int> &previousMines, vector<int> &previousTiles, sf::RenderWindow &window) {
        for (int i = 0; i < board.size(); i++) {
            if(board.at(i) == 1) {
                previousMines.push_back(i);
            }
        }
    }

void restartGame(chrono::time_point<chrono::system_clock> &start, chrono::time_point<chrono::system_clock> &end, chrono::time_point<chrono::system_clock> &startWhenPause, chrono::time_point<chrono::system_clock> &endWhenPause, chrono::duration<double> &timeWhenPaused, int col_, int row_, int mine_, vector<int> &boardVector, vector<tiles> &tilesVector, vector<int> &previousMines, vector<int> &previousClicks,
                 vector<int> &previousFlags, vector<int> &previousNear, vector<int> &revealAllMinesVector, vector<int> &revealAllFlagsVector, vector<chrono::duration<double>> &timeVector,
                 bool &didClickBugTwice, bool &lost, bool &won, bool &play, sf::RenderWindow &SecondWindow) {



    for (int i = 0; i < boardVector.size(); i++) {
        if (boardVector.at(i) == 1) {
            boardVector.at(i) = 0;
        }
    }

    vector<int> test;
    for (int i = 0; i < tilesVector.size();i++) {
        test.push_back(tilesVector.at(i).near);
    }

    tilesVector.clear();
    previousMines.clear();
    previousClicks.clear();
    previousFlags.clear();
    previousNear.clear();
    revealAllMinesVector.clear();
    revealAllFlagsVector.clear();
    didClickBugTwice = false;
    lost = false;
    won = false;
    play = true;


    mt19937 random_mt;
    random_device rd;

    vector<int> random;
    int temp;
    bool valid;
    for (int i = 0; i < mine_ ; i++) {
        uniform_int_distribution<int> dist(0, (row_*col_-1));
        temp = dist(rd);
        for (int j = 0; j < random.size(); j++) {
            if (temp == random.at(j)) {
                valid = false;
                while (!valid) {
                    temp = dist(rd);
                    for (int k = 0; k < random.size(); k++) {
                        if (temp == random.at(k)) {
                            break;
                        }
                        else if (k == random.size()-1 and temp!= random.at(k)) {
                            valid = true;
                        }
                    }
                }
            }
        }
        random.push_back(temp);
        boardVector.at(temp) = 1;
    }

    int xPlus = 0;
    int yPlus = -32;


    for (int i = 0; i < boardVector.size(); i++) {
        if (i % col_ == 0) {
            yPlus += 32;
            xPlus = 0;
        }

        if (boardVector.at(i) == 0) {
            tiles tiles(0 + xPlus, 0 + yPlus);
            tiles.isMine = false;
            tilesVector.push_back(tiles);
            tiles.setTile(SecondWindow,0 + xPlus ,0 + yPlus);
            xPlus += 32;
        } else {
            tiles tiles(0 + xPlus, 0 + yPlus);
            tiles.isMine = true;
            tilesVector.push_back(tiles);
            tiles.setTile(SecondWindow,0 + xPlus ,0 + yPlus);
            xPlus += 32;
        }
    }


    for (int i = 0; i < boardVector.size(); i++) {
        if (tilesVector.at(i).isMine == 1) {
            //top Left corner
            if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 0) {
                tilesVector.at(i + 1).near++;
                tilesVector.at(i + col_).near++;
                tilesVector.at(i + (col_ + 1)).near++;
            }
            //top Right corner
            if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                tilesVector.at(i - 1).near++;
                tilesVector.at(i + (col_ - 1)).near++;
                tilesVector.at(i + col_).near++;
            }
            //Bottom Left corner
            if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 0) {
                tilesVector.at(i + 1).near++;
                tilesVector.at(i - (col_ - 1)).near++;
                tilesVector.at(i - col_).near++;
            }
            //Bottom Right corner
            if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                tilesVector.at(i - 1).near++;
                tilesVector.at(i - col_).near++;
                tilesVector.at(i - (col_ + 1)).near++;
            }
            //Right Side
            if (tilesVector.at(i).yPosition % 32 == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {

                if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                    continue;
                }

                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                    tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                    continue;
                } else {


                    tilesVector.at(i - 1).near++;
                    tilesVector.at(i - col_).near++;
                    tilesVector.at(i - (col_ + 1)).near++;
                    tilesVector.at(i + col_).near++;
                    tilesVector.at(i + (col_ - 1)).near++;
                }
            }
            //Left Side
            if (tilesVector.at(i).yPosition % 32 == 0 and tilesVector.at(i).xPosition == 0) {

                if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 0) {
                    continue;

                }
                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 0) {
                    continue;

                } else {
                    tilesVector.at(i + 1).near++;
                    tilesVector.at(i + col_).near++;
                    tilesVector.at(i + (col_ + 1)).near++;
                    tilesVector.at(i - col_).near++;
                    tilesVector.at(i - (col_ - 1)).near++;

                }
            }
            //Top Side
            if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition % 32 == 0) {

                if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 0) {
                    continue;
                }
                if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                    continue;
                } else {
                    tilesVector.at(i + 1).near++;
                    tilesVector.at(i - 1).near++;
                    tilesVector.at(i + col_).near++;
                    tilesVector.at(i + (col_ + 1)).near++;
                    tilesVector.at(i + (col_ - 1)).near++;


//
                }


            }
            //Bottom Side
            if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition % 32 == 0) {

                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 0) {
                    continue;
                }
                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                    tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                    continue;
                } else {

                    tilesVector.at(i - 1).near++;
                    tilesVector.at(i + 1).near++;
                    tilesVector.at(i - col_).near++;
                    tilesVector.at(i - (col_ - 1)).near++;
                    tilesVector.at(i - (col_ + 1)).near++;


//
                }


            }

            else {
                if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 0) { continue; }
                if (tilesVector.at(i).yPosition == 0 and
                    tilesVector.at(i).xPosition == 32 * (col_ - 1)) { continue; }
                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                    tilesVector.at(i).xPosition == 0) { continue; }
                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                    tilesVector.at(i).xPosition == 32 * (col_ - 1)) { continue; }
                if (tilesVector.at(i).yPosition % 32 == 0 and
                    tilesVector.at(i).xPosition == 32 * (col_ - 1)) { continue; }
                if (tilesVector.at(i).yPosition % 32 == 0 and tilesVector.at(i).xPosition == 0) { continue; }
                if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition % 32 == 0) { continue; }
                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                    tilesVector.at(i).xPosition % 32 == 0) { continue; }

                else {
                    tilesVector.at(i + 1).near++;
                    tilesVector.at(i - 1).near++;
                    tilesVector.at(i - col_).near++;
                    tilesVector.at(i + col_).near++;
                    tilesVector.at(i - (col_-1)).near++;
                    tilesVector.at(i - (col_+1)).near++;
                    tilesVector.at(i + (col_-1)).near++;
                    tilesVector.at(i + (col_+1)).near++;
                }

            }
        }
    }


    drawHappyFaceButton(col_ * 32,row_ * 32 + 100,SecondWindow, lost, won);
    drawDebugButtion(col_ * 32,row_ * 32 + 100,SecondWindow);
    drawPauseButton(col_ * 32,row_ * 32 + 100,SecondWindow);
    drawLeaderboardButton(col_ * 32,row_ * 32 + 100,SecondWindow);

    for (int i = 0; i < tilesVector.size(); i++) {
        tilesVector.at(i).drawTile(SecondWindow);
    }

    start = std::chrono::system_clock::now();
    startWhenPause = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();
    endWhenPause = std::chrono::system_clock::now();
    timeWhenPaused = end - start;
    timeVector.clear();
    SecondWindow.display();

}

void recursiveClick(vector<tiles> &tilesVector, vector<int> &previousClicks, vector<int> &previousNear, int i, int col_, int row_) {

    if (tilesVector.at(i).near == 0 and !tilesVector.at(i).isMine and !tilesVector.at(i).didClick and !tilesVector.at(i).rightClicked) {
        previousClicks.push_back(i);
        tilesVector.at(i).didClick = true;
        tilesVector.at(i).drawFlagTile = false;



        //top Left corner
        if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 0) {
            recursiveClick(tilesVector, previousClicks, previousNear, (i + 1), col_, row_);
            recursiveClick(tilesVector, previousClicks, previousNear, (i + col_), col_, row_);
            recursiveClick(tilesVector, previousClicks, previousNear, (i + (col_ + 1)), col_, row_);
        }
//        //top Right corner
        else if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
            recursiveClick(tilesVector, previousClicks, previousNear, (i - 1), col_, row_);
            recursiveClick(tilesVector, previousClicks, previousNear, (i + (col_ - 1)), col_, row_);
            recursiveClick(tilesVector, previousClicks, previousNear, (i + col_), col_, row_);
        }
//        //Bottom Left corner
        else if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 0) {
            recursiveClick(tilesVector, previousClicks, previousNear, (i + 1), col_, row_);
            recursiveClick(tilesVector, previousClicks, previousNear, (i - (col_ - 1)), col_, row_);
            recursiveClick(tilesVector, previousClicks, previousNear, (i - col_), col_, row_);
        }
//        //Bottom Right corner
        else if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
            recursiveClick(tilesVector, previousClicks, previousNear, (i - 1), col_, row_);
            recursiveClick(tilesVector, previousClicks, previousNear, (i - col_), col_, row_);
            recursiveClick(tilesVector, previousClicks, previousNear, (i - (col_ - 1)), col_, row_);
        }
//        //Right Side
        else if (tilesVector.at(i).yPosition % 32 == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {

                recursiveClick(tilesVector, previousClicks, previousNear, (i - 1), col_, row_);
                recursiveClick(tilesVector, previousClicks, previousNear, (i - col_), col_, row_);
                recursiveClick(tilesVector, previousClicks, previousNear, (i - (col_ + 1)), col_, row_);
                recursiveClick(tilesVector, previousClicks, previousNear, (i + col_), col_, row_);
                recursiveClick(tilesVector, previousClicks, previousNear, (i + (col_ - 1)), col_, row_);
            }
//        //Left Side
        else if (tilesVector.at(i).yPosition % 32 == 0 and tilesVector.at(i).xPosition == 0) {
            recursiveClick(tilesVector, previousClicks,previousNear,(i + 1),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i + col_),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i + (col_+1)),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - col_),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - (col_-1)),col_,row_);
        }
//
////
//        //Top Side
        else if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition % 32 == 0) {
            recursiveClick(tilesVector, previousClicks,previousNear,(i + 1),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - 1),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i + col_),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i + (col_+1)),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i + (col_-1)),col_,row_);


//
            }
////
////        //Bottom Side
        else if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition % 32 == 0) {
            recursiveClick(tilesVector, previousClicks,previousNear,(i - 1),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i + 1),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - col_),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - (col_-1)),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - (col_+1)),col_,row_);


        }

        else {

            recursiveClick(tilesVector, previousClicks,previousNear,(i + 1),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - 1),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - col_),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i + col_),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - (col_-1)),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i - (col_+1)),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i + (col_-1)),col_,row_);
            recursiveClick(tilesVector, previousClicks,previousNear,(i + (col_+1)),col_,row_);

        }
        }

        else if (tilesVector.at(i).near > 0 and !tilesVector.at(i).isMine and !tilesVector.at(i).rightClicked and !tilesVector.at(i).didClick) {
            previousNear.push_back(i);
            previousClicks.push_back(i);
            tilesVector.at(i).didClick = true;
            tilesVector.at(i).drawFlagTile = false;
        }
    }

void drawGameOver(sf::RenderWindow &window, int width, int height) {
    sf::Texture texture;
    texture.loadFromFile("files/images/face_lose.png");
    sf::Sprite sprite(texture);
    sprite.setPosition(width /2 - 25 , height / 2 - 100);
    window.draw(sprite);
}

void drawGameWon(sf::RenderWindow &window, int width, int height) {
    sf::Texture texture;
    texture.loadFromFile("files/images/face_win.png");
    sf::Sprite sprite(texture);
    sprite.setPosition(width /2 - 25 , height / 2 - 100);
    window.draw(sprite);
}

int main()
{

    sf::Texture textureZero;
    textureZero.loadFromFile("files/images/digits.png",sf::IntRect(0,0,21,33));
    sf::Sprite spriteZero(textureZero);

    sf::Texture textureOne;
    textureOne.loadFromFile("files/images/digits.png",sf::IntRect(21,0,21,33));
    sf::Sprite spriteOne(textureOne);

    sf::Texture textureTwo;
    textureTwo.loadFromFile("files/images/digits.png",sf::IntRect(42,0,21,33));
    sf::Sprite spriteTwo(textureTwo);

    sf::Texture textureThree;
    textureThree.loadFromFile("files/images/digits.png",sf::IntRect(63,0,21,33));
    sf::Sprite spriteThree(textureThree);

    sf::Texture textureFour;
    textureFour.loadFromFile("files/images/digits.png",sf::IntRect(84,0,21,33));
    sf::Sprite spriteFour(textureFour);

    sf::Texture textureFive;
    textureFive.loadFromFile("files/images/digits.png",sf::IntRect(105,0,21,33));
    sf::Sprite spriteFive(textureFive);

    sf::Texture textureSix;
    textureSix.loadFromFile("files/images/digits.png",sf::IntRect(126,0,21,33));
    sf::Sprite spriteSix(textureSix);

    sf::Texture textureSeven;
    textureSeven.loadFromFile("files/images/digits.png",sf::IntRect(147,0,21,33));
    sf::Sprite spriteSeven(textureSeven);

    sf::Texture textureEight;
    textureEight.loadFromFile("files/images/digits.png",sf::IntRect(168,0,21,33));
    sf::Sprite spriteEight(textureEight);

    sf::Texture textureNine;
    textureNine.loadFromFile("files/images/digits.png",sf::IntRect(189,0,21,33));
    sf::Sprite spriteNine(textureNine);

    sf::Texture textureMinus;
    textureMinus.loadFromFile("files/images/digits.png",sf::IntRect(210,0,21,33));
    sf::Sprite spriteMinus(textureMinus);


    float width = 800;
    float height = 600;
    string username = "_";
    bool secWindow = false;
    bool triWindow = false;
    bool validName = true;


    sf::RenderWindow Firstwindow(sf::VideoMode(800, 600), "First window");
    sf::Text Title;
    sf::Text inputPrompt;
    sf::Text userText;
    sf::Font font;
    font.loadFromFile("files/font.ttf");

    //for user text
    userText.setFont(font);
    userText.setString(username);
    userText.setCharacterSize(18);
    userText.setFillColor(sf::Color::Yellow);
    userText.setStyle(sf::Text::Bold);
    userText.setPosition(sf::Vector2f(width/2.0f,height/2.0f - 45));

//    for Title
    Title.setFont(font);
    Title.setString("WELCOME TO MINESWEEPER!");
    Title.setCharacterSize(24);
    Title.setFillColor(sf::Color::White);
    Title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect TitleRect = Title.getLocalBounds();
    Title.setOrigin(TitleRect.left + TitleRect.width/2.0f,
                    TitleRect.top + TitleRect.height/2.0f);
    Title.setPosition(sf::Vector2f(width/2.0f,height/2.0f -150));
//    title("WELCOME");

    //for prompt box
    inputPrompt.setFont(font);
    inputPrompt.setString("Enter your name:");
    inputPrompt.setCharacterSize(20);
    inputPrompt.setFillColor(sf::Color::White);
    inputPrompt.setStyle(sf::Text::Bold);
    sf::FloatRect inputPromptRect = inputPrompt.getLocalBounds();
    inputPrompt.setOrigin(inputPromptRect.left + inputPromptRect.width/2.0f,
                    inputPromptRect.top + inputPromptRect.height/2.0f);
    inputPrompt.setPosition(sf::Vector2f(width/2.0f,height/2.0f -75));

    // run the program as long as the window is open
    while (Firstwindow.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (Firstwindow.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                Firstwindow.close();
            }

            else if (event.type == sf::Event::TextEntered) {
                if(event.text.unicode >= 32 && event.text.unicode < 128) {
                    if (isalpha((char)event.text.unicode) and username.length() <= 10) {
                        username.erase(username.length()-1);
                        username += (char)event.text.unicode;
                        username += "_";
                        userText.setString(username);
                    }
                }
            }

            else if(event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (username.size() > 1) {

                    username.erase(username.size()-2);
                    username += "_";
                    userText.setString(username);

                    }
                }
                else if (event.key.code == sf::Keyboard::Enter) {

                    if (username.size() > 1) {

                        for (int i = 0; i <username.length(); i++) {
                            if (username.at(i) == ' ') {
                                validName = false;
                            }
                        }

                        if (validName) {
                            username[0] = toupper(username[0]);
                            for (int i = 1; i < username.length();i++) {
                                username[i] = tolower(username[i]);
                        }
                            secWindow = true;
                            username.pop_back();
                            Firstwindow.close();

                        }
                        validName = true;

                    }

                }
                else if (event.key.code == sf::Keyboard::Space) {
                    username.erase(username.size()-1);
                    username += " _";
                    userText.setString(username);
                }
            }
        }
        Firstwindow.clear(sf::Color::Blue);
        Firstwindow.draw(Title);
        Firstwindow.draw(inputPrompt);
        //Center text before we draw it
        sf::FloatRect userTextRect = userText.getLocalBounds();
        userText.setOrigin(userTextRect.left + userTextRect.width/2.0f,
                           userTextRect.top + userTextRect.height/2.0f);
        Firstwindow.draw(userText);
        Firstwindow.display();
    }


    if (secWindow) {


        ifstream board;
        board.open("files/board_config.cfg");
        int col_;
        int row_;
        int mine_;
        if (board.is_open()) {
            string col;
            string row;
            string mine;
            getline(board, col);
            getline(board, row);
            getline(board, mine);
            col_ = stoi(col);
            row_ = stoi(row);
            mine_ = stoi(mine);
        }

        int SecWidth = col_ * 32;
        int SecHeight = row_ * 32 + 100;
        int UiButtonsXface = ((col_ / 2.0) * 32) - 32;
        int UiButtonsYface = 32 * (row_+0.5f);

        int UiButtonXdebug = (col_ * 32) - 304;
        int UiButtonYdebug = 32 * (row_+0.5f);

        int UiButtonsXpause = (col_ * 32) - 240;
        int UiButtonsYpause = 32 * (row_+0.5f);

        int UiButtonsXleader = (col_ * 32) - 176;
        int UiButtonsYleader = 32 * (row_+0.5f);



        chrono::duration<double> elapsed_seconds;

        sf::RenderWindow SecondWindow(sf::VideoMode(SecWidth, SecHeight), "Second window");


        vector<int> boardVector(row_ * col_, 0);

        vector<tiles> tilesVector;
        vector<int> previousMines;
        vector<int> previousClicks;
        vector<int> previousFlags;
        vector<int> previousNear;
        vector<int> revealAllMinesVector;
        vector<int> revealAllFlagsVector;
        vector<chrono::duration<double>> timeVector;
        string mark = "*";
        bool didClickBugTwice = false;
        bool didClickFlagTwice = false;
        bool drawOtherTimer = false;
        bool play = true;
        bool won = false;
        bool lost = false;


        mt19937 random_mt;
        random_device rd;
        uniform_int_distribution<int> dist(0, (row_*col_-1));


        vector<int> random;
        int temp;
        bool valid;
        for (int i = 0; i < mine_ ; i++) {
            uniform_int_distribution<int> dist(0, (row_*col_-1));
            temp = dist(rd);
            for (int j = 0; j < random.size(); j++) {
                if (temp == random.at(j)) {
                    valid = false;
                    while (!valid) {
                        temp = dist(rd);
                        for (int k = 0; k < random.size(); k++) {
                            if (temp == random.at(k)) {
                                break;
                            }
                            else if (k == random.size()-1 and temp!= random.at(k)) {
                                valid = true;
                            }
                        }
                    }
                }
            }
            random.push_back(temp);
            boardVector.at(temp) = 1;
        }




        int xPlus = 0;
        int yPlus = -32;

        for (int i = 0; i < boardVector.size(); i++) {
            if (i % col_ == 0) {
                yPlus += 32;
                xPlus = 0;
            }

            if (boardVector.at(i) == 0) {
                tiles tiles(0 + xPlus, 0 + yPlus);
                tiles.isMine = false;
                tilesVector.push_back(tiles);
                tiles.setTile(SecondWindow,0 + xPlus ,0 + yPlus);
                xPlus += 32;
            } else {
                tiles tiles(0 + xPlus, 0 + yPlus);
                tiles.isMine = true;
                tilesVector.push_back(tiles);
                tiles.setTile(SecondWindow,0 + xPlus ,0 + yPlus);
                xPlus += 32;
            }
        }



        //adjacent mines
        for (int i = 0; i < boardVector.size(); i++) {

            if (tilesVector.at(i).isMine == 1) {

                //top Left corner
                if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 0) {
                    tilesVector.at(i + 1).near++;
                    tilesVector.at(i + col_).near++;
                    tilesVector.at(i + (col_ + 1)).near++;
                }
                //top Right corner
                if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                    tilesVector.at(i - 1).near++;
                    tilesVector.at(i + (col_ - 1)).near++;
                    tilesVector.at(i + col_).near++;
                }
                //Bottom Left corner
                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 0) {
                    tilesVector.at(i + 1).near++;
                    tilesVector.at(i - (col_ - 1)).near++;
                    tilesVector.at(i - col_).near++;
                }
                //Bottom Right corner
                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                    tilesVector.at(i - 1).near++;
                    tilesVector.at(i - col_).near++;
                    tilesVector.at(i - (col_ + 1)).near++;
                }
                //Right Side
                if (tilesVector.at(i).yPosition % 32 == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {

                    if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                        continue;
                    }

                    if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                        tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                        continue;
                    } else {

                        tilesVector.at(i - 1).near++;
                        tilesVector.at(i - col_).near++;
                        tilesVector.at(i - (col_ + 1)).near++;
                        tilesVector.at(i + col_).near++;
                        tilesVector.at(i + (col_ - 1)).near++;
                    }
                }
                //Left Side
                if (tilesVector.at(i).yPosition % 32 == 0 and tilesVector.at(i).xPosition == 0) {

                    if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 0) {
                        continue;

                    }
                    if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 0) {
                        continue;

                    } else {
                        tilesVector.at(i + 1).near++;
                        tilesVector.at(i + col_).near++;
                        tilesVector.at(i + (col_ + 1)).near++;
                        tilesVector.at(i - col_).near++;
                        tilesVector.at(i - (col_ - 1)).near++;

                    }
                }
                //Top Side
                if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition % 32 == 0) {
                    if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 0) {
                        continue;
                    }
                    if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                        continue;
                    } else {

                        tilesVector.at(i + 1).near++;
                        tilesVector.at(i - 1).near++;
                        tilesVector.at(i + col_).near++;
                        tilesVector.at(i + (col_ + 1)).near++;
                        tilesVector.at(i + (col_ - 1)).near++;


//
                    }


                }
                //Bottom Side
                if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition % 32 == 0) {

                    if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and tilesVector.at(i).xPosition == 0) {
                        continue;
                    }
                    if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                        tilesVector.at(i).xPosition == 32 * (col_ - 1)) {
                        continue;
                    } else {
                        tilesVector.at(i - 1).near++;
                        tilesVector.at(i + 1).near++;
                        tilesVector.at(i - col_).near++;
                        tilesVector.at(i - (col_ - 1)).near++;
                        tilesVector.at(i - (col_ + 1)).near++;


//
                    }


                }

                else {
                    if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition == 0) { continue; }
                    if (tilesVector.at(i).yPosition == 0 and
                        tilesVector.at(i).xPosition == 32 * (col_ - 1)) { continue; }
                    if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                        tilesVector.at(i).xPosition == 0) { continue; }
                    if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                        tilesVector.at(i).xPosition == 32 * (col_ - 1)) { continue; }
                    if (tilesVector.at(i).yPosition % 32 == 0 and
                        tilesVector.at(i).xPosition == 32 * (col_ - 1)) { continue; }
                    if (tilesVector.at(i).yPosition % 32 == 0 and tilesVector.at(i).xPosition == 0) { continue; }
                    if (tilesVector.at(i).yPosition == 0 and tilesVector.at(i).xPosition % 32 == 0) { continue; }
                    if (tilesVector.at(i).yPosition == 32 * (row_ - 1) and
                        tilesVector.at(i).xPosition % 32 == 0) { continue; }

                    else {
                        tilesVector.at(i + 1).near++;
                        tilesVector.at(i - 1).near++;
                        tilesVector.at(i - col_).near++;
                        tilesVector.at(i + col_).near++;
                        tilesVector.at(i - (col_-1)).near++;
                        tilesVector.at(i - (col_+1)).near++;
                        tilesVector.at(i + (col_-1)).near++;
                        tilesVector.at(i + (col_+1)).near++;
                    }

                }
                }
        }


        drawRectangle(col_,row_,SecondWindow);
        drawHappyFaceButton(col_,row_,SecondWindow, lost, won);
        drawDebugButtion(col_,row_,SecondWindow);
        drawPauseButton(col_,row_,SecondWindow);
        drawLeaderboardButton(col_,row_,SecondWindow);
        drawCounter(mine_,row_, col_, tilesVector,spriteZero, spriteOne, spriteTwo, spriteThree, spriteFour, spriteFive,
                    spriteSix, spriteSeven, spriteEight, spriteNine, spriteMinus, SecondWindow);
        for (int i = 0; i < tilesVector.size(); i++) {
            tilesVector.at(i).drawTile(SecondWindow);
        }


        std::chrono::time_point<std::chrono::system_clock> start, end, startWhenPause, endWhenPause;
        chrono::duration<double> timeWhenPaused;
        start = chrono::system_clock::now();

        drawTimer(mine_, row_, col_, tilesVector,spriteZero, spriteOne, spriteTwo, spriteThree, spriteFour, spriteFive,
                  spriteSix, spriteSeven, spriteEight, spriteNine, spriteMinus, SecondWindow, start, end, startWhenPause, endWhenPause, play, lost, won, timeVector);



        SecondWindow.display();

        while (SecondWindow.isOpen()) {


            sf::Event event;
            while (SecondWindow.pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    SecondWindow.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                            int x = sf::Mouse::getPosition(SecondWindow).x;
                            int y = sf::Mouse::getPosition(SecondWindow).y;


                            if (y > row_ * 32) {
                                if ( x >= UiButtonsXface and x <= UiButtonsXface + (row_*4) and y >= UiButtonsYface and y <= UiButtonsYface + (4*row_)) {
                                    restartGame(start, startWhenPause, endWhenPause, end, timeWhenPaused, col_,row_,mine_,boardVector,tilesVector,previousMines,previousClicks,previousFlags,
                                                    previousNear,revealAllMinesVector, revealAllFlagsVector,timeVector, didClickBugTwice, lost, won, play, SecondWindow);
                                }

                                else if ( x >= (UiButtonXdebug) and x<= (UiButtonXdebug + 64) and y >= UiButtonYdebug and y<= UiButtonYdebug + (4*row_) and !lost and !won){
                                    revealAllMines(boardVector,revealAllMinesVector,previousClicks,SecondWindow);
                                        if (!didClickBugTwice) {
                                            didClickBugTwice = true;
                                        }
                                        else{
                                            didClickBugTwice = false;
                                        }
                                }

                                else if (x >= (UiButtonsXpause) and x <= UiButtonsXpause + 64 and y >= UiButtonsYpause and y<= UiButtonsYpause + (4*row_) and !lost and !won) {
                                    if (!play) {
                                        play = true;
                                        for (int i = 0; i < tilesVector.size(); i++) {
                                            tilesVector.at(i).pause = false;
                                        }
                                        endWhenPause = std::chrono::system_clock::now();
                                        chrono::duration<double> timeWhenPaused = endWhenPause - startWhenPause;
                                        timeVector.emplace_back(timeWhenPaused);

                                    }
                                    else {
                                        play = false;
                                        for (int i = 0; i < tilesVector.size(); i++) {
                                            tilesVector.at(i).pause = true;
                                        }
                                        end = std::chrono::system_clock::now();
                                        startWhenPause = std::chrono::system_clock::now();
                                        endWhenPause = std::chrono::system_clock::now();
                                    }
                                }

                                else if (x >= (UiButtonsXleader) and x <= (UiButtonsXleader +64) and  y >= UiButtonsYleader and y<= UiButtonsYleader + (4*row_)) {
                                    int thirdWidth = 16*col_;
                                    int thirdHeight = row_*16 + 50;
                                    sf::RenderWindow ThirdWindow(sf::VideoMode(thirdWidth, thirdHeight), "Third window");
                                    ifstream leaderboard;
                                    leaderboard.open("files/leaderboard.txt");

//

                                    sf::Text placeText;
                                    sf::Text timeText;
                                    sf::Text nameText;
                                    sf::Text leaderboardTitle;
                                    vector<sf::Text> outputTextVector;

                                    leaderboardTitle.setFont(font);
                                    leaderboardTitle.setString("LEADERBOARD");
                                    leaderboardTitle.setCharacterSize(24);
                                    leaderboardTitle.setFillColor(sf::Color::White);
                                    leaderboardTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
                                    sf::FloatRect TitleRect = leaderboardTitle.getLocalBounds();
                                    leaderboardTitle.setOrigin(TitleRect.left + TitleRect.width/2.0f,
                                                    TitleRect.top + TitleRect.height/2.0f);
                                    leaderboardTitle.setPosition(sf::Vector2f(thirdWidth/2.0f,thirdHeight/2.0f -120));


                                    string time;
                                    string name;
                                    bool endWithNumber = true;
                                    int i = 1;
                                    while( getline(leaderboard, time, ',')) {
                                        getline(leaderboard, name);

                                        while (endWithNumber) {
                                            if (name[name.length() - 1] == '1' or name[name.length() - 1] == '2' or
                                                name[name.length() - 1] == '3' or name[name.length() - 1] == '4' or
                                                name[name.length() - 1] == '5' or name[name.length() - 1] == '6'
                                                or name[name.length() - 1] == '7' or name[name.length() - 1] == '8' or
                                                name[name.length() - 1] == '9' or name[name.length() - 1] == '0' or
                                                name[name.length() - 1] == '*') {
                                                name.pop_back();
                                            } else {
                                                endWithNumber = false;
                                            }
                                        }
                                        drawLeaders(col_, row_, i,width,height,name,time,ThirdWindow,placeText, timeText, nameText, font,outputTextVector);
                                        i++;
                                        endWithNumber = true;
                                    }


                                    end = std::chrono::system_clock::now();
                                    startWhenPause = std::chrono::system_clock::now();
//                                    endWhenPause = std::chrono::system_clock::now();
                                    while (ThirdWindow.isOpen())
                                    {

                                        // check all the window's events that were triggered since the last iteration of the loop
                                        sf::Event event;
                                        while (ThirdWindow.pollEvent(event))
                                        {
                                            if (event.type == sf::Event::Closed)
                                                ThirdWindow.close();
                                        }
                                        ThirdWindow.clear(sf::Color::Blue);
                                        ThirdWindow.draw(leaderboardTitle);

                                        for (int i = 0; i < outputTextVector.size(); i+=3) {
                                            ThirdWindow.draw(outputTextVector.at(i));
                                            ThirdWindow.draw(outputTextVector.at(i+1));
                                            ThirdWindow.draw(outputTextVector.at(i+2));
                                        }
                                        for (int k = 0; k < tilesVector.size(); k++) {
                                            tilesVector.at(k).drawClickedTile(SecondWindow);
                                        }
                                        SecondWindow.display();
                                        ThirdWindow.display();
                                    }
                                    endWhenPause = std::chrono::system_clock::now();
                                    chrono::duration<double> timeWhenPaused = endWhenPause - startWhenPause;
                                    timeVector.emplace_back(timeWhenPaused);
                                }

                            }

                            int tempX = x % 32;
                            int tempY = y % 32;
                            x = x - tempX;
                            y = y - tempY;

                        for (int i = 0; i < tilesVector.size(); i++) {
                                if (tilesVector.at(i).xPosition == x and tilesVector.at(i).yPosition == y and !tilesVector.at(i).rightClicked and !tilesVector.at(i).pause and !lost and !won) {

                                    recursiveClick(tilesVector,previousClicks, previousNear,i,col_,row_);

                                    if (tilesVector.at(i).isMine) {
                                        previousMines.push_back(i);
                                        tilesVector.at(i).drawFlagTile = false;
                                    }


                                }
                            }


                    }

                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) and !lost and !won) {
                        int x = sf::Mouse::getPosition(SecondWindow).x;
                        int y = sf::Mouse::getPosition(SecondWindow).y;
                        int tempX = x % 32;
                        int tempY = y % 32;
                        x = x - tempX;
                        y = y - tempY;
                        for (int i = 0; i < tilesVector.size(); i++) {
                            if (tilesVector.at(i).xPosition == x and tilesVector.at(i).yPosition == y) {
                                if (didClickFlagTwice) {
                                    tilesVector.at(i).rightClicked = false;
                                    tilesVector.at(i).notRightClicked = true;
                                    didClickFlagTwice = false;
                                }
                                else {
                                    previousFlags.push_back(i);
                                    tilesVector.at(i).rightClicked = true;
                                    tilesVector.at(i).notRightClicked = false;
                                    didClickFlagTwice = true;
                                }

                            }
                        }
                    }

                }
            }

            drawRectangle(col_,row_,SecondWindow);
            drawHappyFaceButton(col_,row_,SecondWindow, lost, won);
            drawDebugButtion(col_,row_,SecondWindow);
            drawPauseButton(col_,row_,SecondWindow);
            drawLeaderboardButton(col_,row_,SecondWindow);
            drawCounter(mine_, row_, col_, tilesVector,spriteZero, spriteOne, spriteTwo, spriteThree, spriteFour, spriteFive,
                        spriteSix, spriteSeven, spriteEight, spriteNine, spriteMinus, SecondWindow);

            drawTimer(mine_, row_, col_, tilesVector,spriteZero, spriteOne, spriteTwo, spriteThree, spriteFour, spriteFive,
                      spriteSix, spriteSeven, spriteEight, spriteNine, spriteMinus, SecondWindow, start, end, startWhenPause, endWhenPause, play, lost, won, timeVector);

            for (int k = 0; k < tilesVector.size(); k++) {
                tilesVector.at(k).drawTile(SecondWindow);
            }

            for (int k = 0; k < previousClicks.size(); k++) {
                tilesVector.at(previousClicks.at(k)).drawClickedTile(SecondWindow);
            }

            for (int k = 0; k < revealAllMinesVector.size(); k++) {

                if (!didClickBugTwice) {
                    tilesVector.at(revealAllMinesVector.at(k)).drawBomb(SecondWindow);
                }
                else{
                    tilesVector.at(revealAllMinesVector.at(k)).drawTile(SecondWindow);
                }
            }


            for (int k = 0; k < previousNear.size(); k++) {
                if (!tilesVector.at(previousNear.at(k)).rightClicked) {
                    tilesVector.at(previousNear.at(k)).drawNear(SecondWindow);
                }
            }

            if (!play) {
                drawPlayButton(col_,row_,SecondWindow);
            }

            for (int k = 0; k < previousFlags.size(); k++) {
                if (tilesVector.at(previousFlags.at(k)).rightClicked) {
                    tilesVector.at(previousFlags.at(k)).drawFlag(SecondWindow);
                }
            }

            for (int k = 0; k < tilesVector.size(); k++) {
                if(tilesVector.at(k).pause) {
                    tilesVector.at(k).drawClickedTile(SecondWindow);
                }
            }


            //game Won
            for (int k = 0; k < tilesVector.size(); k++) {

                if (!tilesVector.at(k).didClick and !tilesVector.at(k).isMine) {
                    break;
                }
                else if (tilesVector.at(k).didClick and !tilesVector.at(k).isMine and k == tilesVector.size()-1) {

                    revealAllMines(boardVector,revealAllFlagsVector,previousClicks,SecondWindow);
                    for (int j = 0; j < revealAllFlagsVector.size(); j++) {
                        tilesVector.at(revealAllFlagsVector.at(j)).drawFlagReveal(SecondWindow);
                        tilesVector.at(revealAllFlagsVector.at(j)).rightClicked = true;
                    }



                    if (!won) {
                        won = true;
                        drawHappyFaceButton(col_, row_, SecondWindow, lost, won);
                        end = chrono::system_clock::now();
                        elapsed_seconds = end - start;
//
                        for ( int i = 0; i < timeVector.size(); i++) {
                            elapsed_seconds = elapsed_seconds - timeVector.at(i);
                        }

                        SecondWindow.display();


                        int thirdWidth = 16*col_;
                        int thirdHeight = row_*16 + 50;
                        sf::RenderWindow ThirdWindow(sf::VideoMode(thirdWidth, thirdHeight), "Third window");
                        fstream leaderboard;
                        leaderboard.open("files/leaderboard.txt");

                        sf::Text placeText;
                        sf::Text timeText;
                        sf::Text nameText;
                        sf::Text leaderboardTitle;
                        vector<sf::Text> outputTextVector;

                        leaderboardTitle.setFont(font);
                        leaderboardTitle.setString("LEADERBOARD");
                        leaderboardTitle.setCharacterSize(24);
                        leaderboardTitle.setFillColor(sf::Color::White);
                        leaderboardTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
                        sf::FloatRect TitleRect = leaderboardTitle.getLocalBounds();
                        leaderboardTitle.setOrigin(TitleRect.left + TitleRect.width/2.0f,
                                                   TitleRect.top + TitleRect.height/2.0f);
                        leaderboardTitle.setPosition(sf::Vector2f(thirdWidth/2.0f,thirdHeight/2.0f -120));



                        //organize leaderboard here.
                        map<string,int> MapOfLeaders;
                        map<string,int>::iterator MapOfLeadersIter;


                        //Gets strings for name and time, and adds them to a map. Takes the time and converts it to seconds
                        username = username + mark;
                        string Checktime;
                        string Checkname;

                        while (getline(leaderboard, Checktime, ',')) {
//                            getline(leaderboard, Checktime, ',');
                            getline(leaderboard, Checkname);
                            bool minutes = true;
                            bool aster = true;
                            string tempMinutes = "";
                            string tempSeconds = "";
                            string tempName = "";

                            for (int i = 0; i < Checktime.length(); i++) {

                                if (Checktime[i] == ':' ) {
                                    minutes = false;
                                }

                                else if (minutes) {
                                    tempMinutes += Checktime[i];
                                }

                                else if (!minutes) {
                                    tempSeconds += Checktime[i];
                                }
                            }

                            for (int i = 0; i < Checkname.length(); i++) {
                                if (Checkname[i] == '*' ) {
                                    aster = false;
                                    tempName = tempName + to_string(i);
                                }
                                else if (aster) {
                                    tempName += Checkname[i];
                                }


                            }


                            random_device rd2;
                            int temps = dist(rd2);
                            Checkname = tempName + to_string((temps));
                            int time = (stoi(tempMinutes) * 60) + stoi(tempSeconds);
                            MapOfLeaders[Checkname] = time;
                        }




                        //Gets userTime (userName is already stored)
                        string Time = to_string(chrono::duration_cast<chrono::seconds>(elapsed_seconds).count());
                        int userTime = stoi(Time);


                        // See if userTime is better than any other time on the leaderboard and if it is then we add it to map
                        bool proceed = false;
                        for (MapOfLeadersIter = MapOfLeaders.begin(); MapOfLeadersIter != MapOfLeaders.end(); MapOfLeadersIter++) {
                             if (userTime < MapOfLeadersIter->second) {
                                 MapOfLeaders[username] = userTime;
                                 proceed = true;
                             }
                         }


                            //if we can proceed, find the slowest (biggest) time and DELETE that element;
                        if (proceed) {
                             int max = 0;
                             string remove = "";
                             for (MapOfLeadersIter = MapOfLeaders.begin();
                                  MapOfLeadersIter != MapOfLeaders.end(); MapOfLeadersIter++) {
                                 if (max < MapOfLeadersIter->second) {
                                     max = MapOfLeadersIter->second;
                                     remove = MapOfLeadersIter->first;
                                 }
                             }
                             MapOfLeaders.erase(remove);


                            //Now we want to write to the file with these names and times in the correct order.
                            //First we organize


                            // create an empty vector of pairs
                            vector<pair<string, int>> vec;

                            // copy key-value pairs from the map to the vector
                            map<string, int> :: iterator it2;
                            for (it2=MapOfLeaders.begin(); it2!=MapOfLeaders.end(); it2++)
                            {
                                vec.push_back(make_pair(it2->first, it2->second));
                            }

                            // // sort the vector by increasing order of its pair's second value
                            sort(vec.begin(), vec.end(), sort_);



                            //now we want to convert the int to a string to match the needed format;
                            ofstream output("files/leaderboard.txt");

                            for (int i = 0; i < vec.size(); i++)
                            {
                                string temp = "";

                                if (vec[i].second < 10) {
                                    temp = "00:0" + to_string(vec[i].second);
                                }
                                else if (vec[i].second < 60) {
                                    temp = "00:" + to_string(vec[i].second);
                                }
                                else if (vec[i].second > 60) {
                                    string seconds = to_string(vec[i].second % 60);
                                    string minutes = to_string(vec[i].second / 60);

                                    if (minutes.length() == 1) {
                                        minutes =  "0" + minutes + ":";
                                    }

                                    else if (minutes.length() > 1) {
                                        minutes = minutes + ":";
                                    }

                                    if (seconds.length() == 1) {
                                        seconds =  "0" + seconds + ":";
                                    }

                                    else if (seconds.length() > 1) {
                                        seconds = seconds + ":";
                                    }

                                    temp = minutes + seconds;

                                    if (temp.length() > 4) {
                                        temp.pop_back();
                                    }

                                }
                                output << temp << ",";
                                output << vec[i].first << endl;
                            }
                            }


                            //now we write from file to screen
                        ifstream read("files/leaderboard.txt");

                        string time;
                        string name;
                        bool endWithNumber = true;
                        int i = 1;
                        while( getline(read, time, ',')) {
                            getline(read, name);

                            while (endWithNumber and proceed) {

                                if(name[name.length()-1] == '1' or name[name.length()-1] == '2' or name[name.length()-1] == '3' or name[name.length()-1] == '4' or name[name.length()-1] == '5' or name[name.length()-1] == '6'
                                   or name[name.length()-1] == '7' or name[name.length()-1] == '8' or name[name.length()-1] == '9' or name[name.length()-1] == '0') {
                                    name.pop_back();
                                }

                                else {
                                    endWithNumber = false;
                                }
                            }

                            while (endWithNumber and !proceed) {

                                if(name[name.length()-1] == '1' or name[name.length()-1] == '2' or name[name.length()-1] == '3' or name[name.length()-1] == '4' or name[name.length()-1] == '5' or name[name.length()-1] == '6'
                                   or name[name.length()-1] == '7' or name[name.length()-1] == '8' or name[name.length()-1] == '9' or name[name.length()-1] == '0' or name[name.length()-1] == '*' ) {
                                    name.pop_back();
                                }

                                else {
                                    endWithNumber = false;
                                }
                            }

                            drawLeaders(col_, row_, i,width,height,name,time,ThirdWindow,placeText, timeText, nameText, font,outputTextVector);
                            i++;
                            endWithNumber = true;
                        }


                        while (ThirdWindow.isOpen())
                        {
                            // check all the window's events that were triggered since the last iteration of the loop
                            sf::Event event;
                            while (ThirdWindow.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    ThirdWindow.close();
                            }
                            ThirdWindow.clear(sf::Color::Blue);
                            ThirdWindow.draw(leaderboardTitle);

                            for (int i = 0; i < outputTextVector.size(); i+=3) {
                                ThirdWindow.draw(outputTextVector.at(i));
                                ThirdWindow.draw(outputTextVector.at(i+1));
                                ThirdWindow.draw(outputTextVector.at(i+2));
                            }
                            ThirdWindow.display();
                        }
                    }

                    revealAllMinesVector.clear();
                }
            }

            //Game Over
            for (int k = 0; k < previousMines.size(); k++) {
                
                revealAllMines(boardVector, revealAllMinesVector, previousClicks, SecondWindow);
                for (int k = 0; k < revealAllMinesVector.size(); k++) {
                    tilesVector.at(revealAllMinesVector.at(k)).drawBomb(SecondWindow);
                }

                if (!lost) {
                    end = chrono::system_clock::now();
                    elapsed_seconds = end - start;

                    for ( int i = 0; i < timeVector.size(); i++) {
                        elapsed_seconds = elapsed_seconds - timeVector.at(i);
                    }
                }
                lost = true;
                drawHappyFaceButton(col_, row_, SecondWindow, lost, won);
            }

            SecondWindow.display();
        }
    }
    return 0;
}
