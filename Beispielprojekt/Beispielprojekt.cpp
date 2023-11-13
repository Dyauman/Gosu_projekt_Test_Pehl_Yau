#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <cmath>
#include<iostream>
#include<string>

//Eigene Klasse fuer Koordinaten
class Coordinates {
public:
    double x, y, hitmarker_x, hitmarker_y;
    Coordinates(double startX, double startY, double hitX, double hitY) 
        : x(startX), y(startY), hitmarker_x(hitX), hitmarker_y(hitY) 
    {}

    //Get Methoden um die Koordinaten von der Klasse zu bekommen
    double getCoordinate_X()
    {
        return x;
    }

    double getCoordinate_hitX()
    {
        return hitmarker_x;
    }

    
};

//Alter code teil fuer Player, kann entfernt werden wenn es nicht mehr benoetigt wird

/*
class Player {
public:
    double x, y, marker1, marker2, marker3;      
    double direction; // 1 für rechts, -1 für links
    bool leftKeyPressed;
    bool rightKeyPressed;
    int keyHold_l;      //Variable fuer kontinuierliche Bewegung
    int keyHold_r;

    Player(double startX, double startY, bool left, bool right)
        : x(startX), y(startY), leftKeyPressed(left), rightKeyPressed(right), keyHold_r(0), keyHold_l(0), direction(1)
    {}
    void move(double direction) {
        this->x = this->x + direction;
        this->marker1 = this->marker1 + direction;
        this->marker2 = this->marker2 + direction;
        this->marker3 = this->marker3 + direction;
    }
};
*/

//Player Klasse mit Erbung der Koordinaten
class Player : public Coordinates {
public:
    double direction; // 1 für rechts, -1 für links
    bool leftKeyPressed;
    bool rightKeyPressed;
    int keyHold_r;      //Variable fuer kontinuierliche Bewegung
    int keyHold_l;
    int lifePoints;
    

    Player(double startX, double startY, double hitX, double hitY, bool left, bool right)
        : Coordinates(startX,startY,hitX, hitY), leftKeyPressed(left), rightKeyPressed(right), keyHold_r(0), keyHold_l(0), direction(1), lifePoints(3)
    {}

    void move(double direction) {
        this->x = this->x + direction;
        this->hitmarker_x = this->hitmarker_x + direction;
    }

    //Methode falls ein Treffer gelandet wurde
    void startPos(Player& p1, Player& p2)
    {
        p1.x = 300;
        p1.hitmarker_x = 300;

        p2.x = 1620;
        p2.hitmarker_x = 1620;

    }

    //Methode fuer Angriff, falls Schwertposition groesser ist als gegnerischer Player => Hit
    bool hit(double swordPos, double hitmarkerPos, int side, Player& p)
    {
        if ((swordPos >= hitmarkerPos) && side == 0)
        {
            Gosu::Font(24).draw_text("You have been slained by xXPu$$ySl4y3rXx", 860, 300, 1, 1, 1);
            
            if (p.lifePoints == 1)
            {
                Gosu::Font(24).draw_text("Player xXPu$$ySl4y3rXx has won!", 860, 300, 1, 1, 1);
            }
            else
            {
                p.lifePoints = p.lifePoints - 1;
            }
            return true;
        }
        else
        {
            if (swordPos <= hitmarkerPos && side == 1)
            {
                Gosu::Font(24).draw_text("You have been slained by xXD1cKSl4y3rXx", 860, 300, 1, 1, 1);

                if (p.lifePoints == 1)
                {
                    Gosu::Font(24).draw_text("Player xXD1cKSl4y3rXx has won!", 860, 300, 1, 1, 1);
                }
                else
                {
                    p.lifePoints = p.lifePoints - 1;
                }
                return true;
            }
        }
        return false;
    }

};

class Sword {
public:
    int swordPosition;
    double swordLength_idle;
    double swordLength_extended;
    bool upKeyPressed;
    bool downKeyPressed;
    bool extendingSword;
    unsigned long cooldown;

    Sword(int p, bool upKey, bool downKey, bool extending, double idle, double extended, unsigned long cd)
        : swordPosition(p), upKeyPressed(upKey), downKeyPressed(downKey), extendingSword(extending), swordLength_idle(idle), swordLength_extended(extended), cooldown(cd)
    {}

    //Methode fuer die Schwertlaenge
    double get_swordLength_extended()
    {
        return swordLength_extended;
    }

    double get_swordLength_idle()
    {
        return swordLength_idle;
    }

    //Methode falls ein Treffer gelandet wurde
    void startSwordPos(Sword& s1, Sword& s2)
    {
        s1.swordPosition = 0;
        s2.swordPosition = 0;
    }
};

class GameWindow : public Gosu::Window
{
public:
    GameWindow()
        : Window(1920, 1080) { // Größe des Fensters
        set_caption("Nidhogg Fake");
         
    }

    Player player1 = Player(300, 540, 300, 540, false, false); // Startposition des ersten Spielers
    Player player2 = Player(1620, 540, 1620, 540, false, false); // Startposition des zweiten Spielers
    Sword swordPlayer1 = Sword(0, false, false, false, 70, 120, 0);     //Schwertposition des ersten Spielers
    Sword swordPlayer2 = Sword(0, false, false, false, 70, 120, 0);    //Schwertposition des zweiten Spielers

    int steps = 50;                                 //Dynamische Variable fuer die Schrittweite
    int steps_divider = 5;                          //Dynamische Variable fuer mehrere Schritte
  

    void draw() override {
        
        
        std::string text1 = "Player 1 LP:" + std::to_string(player1.lifePoints);
        Gosu::Font(24).draw_text(text1, double(250), double(400), 1);
        double textwidth1 =  1575 - Gosu::Font(24).text_width(text1);
        std::string text2 = "Player 2 LP" + std::to_string(player2.lifePoints);
        Gosu::Font(24).draw_text(text2, textwidth1, double(400), 0);
        
        //Player 1 Angriffsposition
        // Kopf
       if (swordPlayer1.extendingSword == true)
       {
            drawCircle(player1.x, player1.y, 25, Gosu::Color::GREEN);

            // Körper
            graphics().draw_line(player1.x, player1.y + 25, Gosu::Color::GREEN,
                player1.x - 20, player1.y + 100, Gosu::Color::GREEN,
                0.0);
            // Schwertarm
            if (swordPlayer1.swordPosition == 2) {
                //Oben
                graphics().draw_line(player1.x -10, player1.y + 50, Gosu::Color::GREEN,
                    player1.x + 40, player1.y + 75, Gosu::Color::GREEN,
                    0.0);
                //Schwert
                graphics().draw_line(player1.x + 40, player1.y + 75, Gosu::Color::BLUE,
                    player1.x + swordPlayer1.swordLength_extended, player1.y + 75, Gosu::Color::BLUE,
                    0.0);
                graphics().draw_line(player1.x + 45, player1.y + 85, Gosu::Color::BLUE,
                    player1.x + 45, player1.y + 65, Gosu::Color::BLUE,
                    0.0);
            //Wenn die Schwertposition beim Angriff ungleich der Schwertposition des Gegners ist wird Methode aufgerufen
                if (swordPlayer1.swordPosition != swordPlayer2.swordPosition)
                {
                    //Falls Treffer, bringe beide Player wieder in Start Position
                    if (player1.hit((player1.getCoordinate_X() + swordPlayer1.get_swordLength_extended()), player2.getCoordinate_hitX(), 0, player2))
                    {
                        player1.startPos(player1, player2);
                        swordPlayer1.startSwordPos(swordPlayer1, swordPlayer2);
                    }
                }
                
            }
            else if (swordPlayer1.swordPosition == 1) {
                //Mitte
                graphics().draw_line(player1.x-10, player1.y + 50, Gosu::Color::GREEN,
                    player1.x + 40, player1.y + 50, Gosu::Color::GREEN,
                    0.0);
                //Schwert
                graphics().draw_line(player1.x + 40, player1.y + 50, Gosu::Color::BLUE,
                    player1.x + swordPlayer1.swordLength_extended, player1.y + 50, Gosu::Color::BLUE,
                    0.0);
                graphics().draw_line(player1.x + 45, player1.y + 60, Gosu::Color::BLUE,
                    player1.x + 45, player1.y + 40, Gosu::Color::BLUE,
                    0.0);
                //Wenn die Schwertposition beim Angriff ungleich der Schwertposition des Gegners ist wird Methode aufgerufen
                if (swordPlayer1.swordPosition != swordPlayer2.swordPosition)
                {
                    //Falls Treffer, bringe beide Player wieder in Start Position
                    if (player1.hit((player1.getCoordinate_X() + swordPlayer1.get_swordLength_extended()), player2.getCoordinate_hitX(), 0, player2))
                    {
                        player1.startPos(player1, player2);
                        swordPlayer1.startSwordPos(swordPlayer1, swordPlayer2);
                    }
                }
            }
            else if (swordPlayer1.swordPosition == 0) {
                //Unten
                graphics().draw_line(player1.x -10, player1.y + 50, Gosu::Color::GREEN,
                    player1.x + 40, player1.y + 25, Gosu::Color::GREEN,
                    0.0);
                //Schwert
                graphics().draw_line(player1.x + 40, player1.y + 25, Gosu::Color::BLUE,
                    player1.x + swordPlayer1.swordLength_extended, player1.y + 25, Gosu::Color::BLUE,
                    0.0);
                graphics().draw_line(player1.x + 45, player1.y + 35, Gosu::Color::BLUE,
                    player1.x + 45, player1.y + 15, Gosu::Color::BLUE,
                    0.0);
                //Wenn die Schwertposition beim Angriff ungleich der Schwertposition des Gegners ist wird Methode aufgerufen
                if (swordPlayer1.swordPosition != swordPlayer2.swordPosition)
                {
                    //Falls Treffer, bringe beide Player wieder in Start Position
                    if (player1.hit((player1.getCoordinate_X() + swordPlayer1.get_swordLength_extended()), player2.getCoordinate_hitX(), 0, player2))
                    {
                        player1.startPos(player1, player2);
                        swordPlayer1.startSwordPos(swordPlayer1, swordPlayer2);
                    }
                }
            }
            // linker Arm 
            graphics().draw_line(player1.x -10 , player1.y + 50, Gosu::Color::GREEN,
                player1.x - 30, player1.y + 50, Gosu::Color::GREEN,
                0.0);
            graphics().draw_line(player1.x - 30, player1.y + 50, Gosu::Color::GREEN,
                player1.x - 60, player1.y + 30, Gosu::Color::GREEN,
                0.0);

            // rechtes Bein
            graphics().draw_line(player1.x - 20, player1.y + 100, Gosu::Color::GREEN,
                player1.x + 20, player1.y + 100, Gosu::Color::GREEN,
                0.0);
            graphics().draw_line(player1.x +20, player1.y + 100, Gosu::Color::GREEN,
                player1.x + 20, player1.y + 120, Gosu::Color::GREEN,
                0.0);


            // linkes Bein
            graphics().draw_line(player1.x -20, player1.y + 100, Gosu::Color::GREEN,
                player1.x - 50, player1.y + 120, Gosu::Color::GREEN,
                0.0);

            

        }

       //Player 1 Ruheposition
        else
        {
            drawCircle(player1.x, player1.y, 25, Gosu::Color::GREEN);

            // Körper
            graphics().draw_line(player1.x, player1.y + 25, Gosu::Color::GREEN,
                player1.x, player1.y + 100, Gosu::Color::GREEN,
                0.0);
            // Schwertarm
            if (swordPlayer1.swordPosition == 2) {
                //Oben
                graphics().draw_line(player1.x, player1.y + 50, Gosu::Color::GREEN,
                    player1.x + 15, player1.y + 75, Gosu::Color::GREEN,
                    0.0);
                //Schwert
                graphics().draw_line(player1.x + 15, player1.y + 75, Gosu::Color::BLUE,
                    player1.x + swordPlayer1.swordLength_idle, player1.y + 75, Gosu::Color::BLUE,
                    0.0);
                graphics().draw_line(player1.x + 20, player1.y + 85, Gosu::Color::BLUE,
                    player1.x + 20, player1.y + 65, Gosu::Color::BLUE,
                    0.0);
            }
            else if (swordPlayer1.swordPosition == 1) {
                //Mitte
                graphics().draw_line(player1.x, player1.y + 50, Gosu::Color::GREEN,
                    player1.x + 15, player1.y + 50, Gosu::Color::GREEN,
                    0.0);
                //Schwert
                graphics().draw_line(player1.x + 15, player1.y + 50, Gosu::Color::BLUE,
                    player1.x + swordPlayer1.swordLength_idle, player1.y + 50, Gosu::Color::BLUE,
                    0.0);
                graphics().draw_line(player1.x + 20, player1.y + 60, Gosu::Color::BLUE,
                    player1.x + 20, player1.y + 40, Gosu::Color::BLUE,
                    0.0);
            }
            else if (swordPlayer1.swordPosition == 0) {
                //Unten
                graphics().draw_line(player1.x, player1.y + 50, Gosu::Color::GREEN,
                    player1.x + 15, player1.y + 25, Gosu::Color::GREEN,
                    0.0);
                //Schwert
                graphics().draw_line(player1.x + 15, player1.y + 25, Gosu::Color::BLUE,
                    player1.x + swordPlayer1.swordLength_idle, player1.y + 25, Gosu::Color::BLUE,
                    0.0);
                graphics().draw_line(player1.x + 20, player1.y + 35, Gosu::Color::BLUE,
                    player1.x + 20, player1.y + 15, Gosu::Color::BLUE,
                    0.0);
            }
            // linker Arm 
            graphics().draw_line(player1.x, player1.y + 50, Gosu::Color::GREEN,
                player1.x - 30, player1.y + 50, Gosu::Color::GREEN,
                0.0);
            graphics().draw_line(player1.x - 30, player1.y + 50, Gosu::Color::GREEN,
                player1.x, player1.y + 80, Gosu::Color::GREEN,
                0.0);

            // rechtes Bein
            graphics().draw_line(player1.x, player1.y + 100, Gosu::Color::GREEN,
                player1.x + 30, player1.y + 120, Gosu::Color::GREEN,
                0.0);

            // linkes Bein
            graphics().draw_line(player1.x, player1.y + 100, Gosu::Color::GREEN,
                player1.x - 30, player1.y + 120, Gosu::Color::GREEN,
                0.0);
        }
        


        //Player 2 Angriffsposition
        // Kopf
       if (swordPlayer2.extendingSword == true)
       {
           drawCircle(player2.x, player2.y, 25, Gosu::Color::WHITE);


           // Körper 
           graphics().draw_line(player2.x, player2.y + 25, Gosu::Color::WHITE,
               player2.x + 20, player2.y + 100, Gosu::Color::WHITE,
               0.0);

           // rechter Arm
           graphics().draw_line(player2.x + 10, player2.y + 50, Gosu::Color::WHITE,
               player2.x + 30, player2.y + 50, Gosu::Color::WHITE,
               0.0);
           graphics().draw_line(player2.x + 30, player2.y + 50, Gosu::Color::WHITE,
               player2.x + 60, player2.y + 30, Gosu::Color::WHITE,
               0.0);

           //Schwertarm 
           if (swordPlayer2.swordPosition == 2) {
               //Unten
               graphics().draw_line(player2.x + 10, player2.y + 50, Gosu::Color::WHITE,
                   player2.x - 40, player2.y + 75, Gosu::Color::WHITE,
                   0.0);
               //Schwert
               graphics().draw_line(player2.x - 40, player2.y + 75, Gosu::Color::BLUE,
                   player2.x - swordPlayer2.swordLength_extended, player2.y + 75, Gosu::Color::BLUE,
                   0.0);
               graphics().draw_line(player2.x - 45, player2.y + 85, Gosu::Color::BLUE,
                   player2.x - 45, player2.y + 65, Gosu::Color::BLUE,
                   0.0);
               //Wenn die Schwertposition beim Angriff ungleich der Schwertposition des Gegners ist wird Methode aufgerufen
               if (swordPlayer2.swordPosition != swordPlayer1.swordPosition)
               {
                   //Falls Treffer, bringe beide Player wieder in Start Position
                   if (player2.hit((player2.getCoordinate_X() - swordPlayer2.get_swordLength_extended()), player1.getCoordinate_hitX(), 1, player1))
                   {
                       player2.startPos(player1, player2);
                       swordPlayer2.startSwordPos(swordPlayer1, swordPlayer2);
                   }
               }
           }
           else  if (swordPlayer2.swordPosition == 1) {
               //Mitte
               graphics().draw_line(player2.x + 10, player2.y + 50, Gosu::Color::WHITE,
                   player2.x - 40, player2.y + 50, Gosu::Color::WHITE,
                   0.0);
               //Schwert
               graphics().draw_line(player2.x - 40, player2.y + 50, Gosu::Color::BLUE,
                   player2.x - swordPlayer2.swordLength_extended, player2.y + 50, Gosu::Color::BLUE,
                   0.0);
               graphics().draw_line(player2.x - 45, player2.y + 60, Gosu::Color::BLUE,
                   player2.x - 45, player2.y + 40, Gosu::Color::BLUE,
                   0.0);
               //Wenn die Schwertposition beim Angriff ungleich der Schwertposition des Gegners ist wird Methode aufgerufen
               if (swordPlayer2.swordPosition != swordPlayer1.swordPosition)
               {
                   //Falls Treffer, bringe beide Player wieder in Start Position
                   if (player2.hit((player2.getCoordinate_X() - swordPlayer2.get_swordLength_extended()), player1.getCoordinate_hitX(), 1, player1))
                   {
                       player2.startPos(player1, player2);
                       swordPlayer2.startSwordPos(swordPlayer1, swordPlayer2);
                   }
               }
           }
           else if (swordPlayer2.swordPosition == 0) {
               //Oben
               graphics().draw_line(player2.x + 10, player2.y + 50, Gosu::Color::WHITE,
                   player2.x - 40, player2.y + 25, Gosu::Color::WHITE,
                   0.0);
               //Schwert
               graphics().draw_line(player2.x - 40, player2.y + 25, Gosu::Color::BLUE,
                   player2.x - swordPlayer2.swordLength_extended, player2.y + 25, Gosu::Color::BLUE,
                   0.0);
               graphics().draw_line(player2.x - 45, player2.y + 35, Gosu::Color::BLUE,
                   player2.x - 45, player2.y + 15, Gosu::Color::BLUE,
                   0.0);
               //Wenn die Schwertposition beim Angriff ungleich der Schwertposition des Gegners ist wird Methode aufgerufen
               if (swordPlayer2.swordPosition != swordPlayer1.swordPosition)
               {
                   //Falls Treffer, bringe beide Player wieder in Start Position
                   if (player2.hit((player2.getCoordinate_X() - swordPlayer2.get_swordLength_extended()), player1.getCoordinate_hitX(), 1, player1))
                   {
                       player2.startPos(player1, player2);
                       swordPlayer2.startSwordPos(swordPlayer1, swordPlayer2);
                   }
               }
           }

           // rechtes Bein
           graphics().draw_line(player2.x + 20, player2.y + 100, Gosu::Color::WHITE,
               player2.x - 20, player2.y + 100, Gosu::Color::WHITE,
               0.0);
           graphics().draw_line(player2.x - 20, player2.y + 100, Gosu::Color::WHITE,
               player2.x - 20, player2.y + 120, Gosu::Color::WHITE,
               0.0);

           // linkes Bein
           graphics().draw_line(player2.x + 20, player2.y + 100, Gosu::Color::WHITE,
               player2.x + 50, player2.y + 120, Gosu::Color::WHITE,
               0.0);  // linkes Bein
       }
       else
       {
           //Player 2 Ruheposition
         // Kopf

           drawCircle(player2.x, player2.y, 25, Gosu::Color::WHITE);


           // Körper 
           graphics().draw_line(player2.x, player2.y + 25, Gosu::Color::WHITE,
               player2.x, player2.y + 100, Gosu::Color::WHITE,
               0.0);

           // rechter Arm
           graphics().draw_line(player2.x, player2.y + 50, Gosu::Color::WHITE,
               player2.x + 30, player2.y + 50, Gosu::Color::WHITE,
               0.0);
           graphics().draw_line(player2.x + 30, player2.y + 50, Gosu::Color::WHITE,
               player2.x, player2.y + 80, Gosu::Color::WHITE,
               0.0);

           //Schwertarm 
           if (swordPlayer2.swordPosition == 2) {
               //Unten
               graphics().draw_line(player2.x, player2.y + 50, Gosu::Color::WHITE,
                   player2.x - 15, player2.y + 75, Gosu::Color::WHITE,
                   0.0);
               //Schwert
               graphics().draw_line(player2.x - 15, player2.y + 75, Gosu::Color::BLUE,
                   player2.x - swordPlayer2.swordLength_idle, player2.y + 75, Gosu::Color::BLUE,
                   0.0);
               graphics().draw_line(player2.x - 20, player2.y + 85, Gosu::Color::BLUE,
                   player2.x - 20, player2.y + 65, Gosu::Color::BLUE,
                   0.0);
           }
           else  if (swordPlayer2.swordPosition == 1) {
               //Mitte
               graphics().draw_line(player2.x, player2.y + 50, Gosu::Color::WHITE,
                   player2.x - 15, player2.y + 50, Gosu::Color::WHITE,
                   0.0);
               //Schwert
               graphics().draw_line(player2.x - 15, player2.y + 50, Gosu::Color::BLUE,
                   player2.x - swordPlayer2.swordLength_idle, player2.y + 50, Gosu::Color::BLUE,
                   0.0);
               graphics().draw_line(player2.x - 20, player2.y + 60, Gosu::Color::BLUE,
                   player2.x - 20, player2.y + 40, Gosu::Color::BLUE,
                   0.0);
           }
           else if (swordPlayer2.swordPosition == 0) {
               //Oben
               graphics().draw_line(player2.x, player2.y + 50, Gosu::Color::WHITE,
                   player2.x - 15, player2.y + 25, Gosu::Color::WHITE,
                   0.0);
               //Schwert
               graphics().draw_line(player2.x - 15, player2.y + 25, Gosu::Color::BLUE,
                   player2.x - swordPlayer2.swordLength_idle, player2.y + 25, Gosu::Color::BLUE,
                   0.0);
               graphics().draw_line(player2.x - 20, player2.y + 35, Gosu::Color::BLUE,
                   player2.x - 20, player2.y + 15, Gosu::Color::BLUE,
                   0.0);
           }

           // rechtes Bein
           graphics().draw_line(player2.x, player2.y + 100, Gosu::Color::WHITE,
               player2.x + 30, player2.y + 120, Gosu::Color::WHITE,
               0.0);

           // linkes Bein
           graphics().draw_line(player2.x, player2.y + 100, Gosu::Color::WHITE,
               player2.x - 30, player2.y + 120, Gosu::Color::WHITE,
               0.0);  // linkes Bein
       }
    }

    //Funktion zum Zeichnen eines Kreises
    void drawCircle(double x, double y, double radius, Gosu::Color color)
    {
        for (int i = 0; i <= 360; i++)
        {
            double angle = i * M_PI / 180.0;
            double x1 = x + radius * cos(angle);
            double y1 = y + radius * sin(angle);
            double x2 = x + radius * cos(angle + M_PI / 180.0);
            double y2 = y + radius * sin(angle + M_PI / 180.0);

            graphics().draw_line(x1, y2, color, x2, y2, color, 0.0);
        }
    }

    void update() override {

        if (input().down(Gosu::KB_A)) {
            //Einzelne Bewegung
            if (!player1.leftKeyPressed) {
                player1.leftKeyPressed = true;
                player1.move(-steps);
            }
            //Kontinuierliche Bewegung
            player1.keyHold_l = player1.keyHold_l + 1;

            if (player1.keyHold_l >= 30)
            {
                player1.move(-steps / steps_divider);
            }
        }
        else
        {
            player1.leftKeyPressed = false;
            player1.keyHold_l = 0;
        }

        if (input().down(Gosu::KB_D) && (player1.getCoordinate_X() < player2.getCoordinate_X() - 100)) {
            //Einzelne Bewegung
            if (!player1.rightKeyPressed) {
                player1.rightKeyPressed = true;
                player1.move(steps);
            }
            //Kontinuierliche Bewegung
            player1.keyHold_r = player1.keyHold_r + 1;

            if (player1.keyHold_r >= 30)
            {
                player1.move(steps / steps_divider);
            }
        }
        else
        {
            player1.rightKeyPressed = false;
            player1.keyHold_r = 0;
        }

        // Steuerung für Spieler 2

        if (input().down(Gosu::KB_LEFT) && (player2.getCoordinate_X() > player1.getCoordinate_X() + 100)) {
            //Einzelne Bewegung 
            if (!player2.leftKeyPressed) {
                player2.leftKeyPressed = true;
                player2.move(-steps);
            }

            //Kontinuierliche Bewegung
            player2.keyHold_l = player2.keyHold_l + 1;

            if (player2.keyHold_l >= 30)
            {
                player2.move(-steps / steps_divider);
            }
        }
        else
        {
            player2.leftKeyPressed = false;
            player2.keyHold_l = 0;
        }

        if (input().down(Gosu::KB_RIGHT)) {
            //Einzelne Bewegung
            if (!player2.rightKeyPressed) {
                player2.rightKeyPressed = true;
                player2.move(steps);
            }

            //Kontinuierliche Bewegung
            player2.keyHold_r = player2.keyHold_r + 1;

            if (player2.keyHold_r >= 30)
            {
                player2.move(steps / steps_divider);
            }
        }
        else
        {
            player2.rightKeyPressed = false;
            player2.keyHold_r = 0;
        }


        // Bewegung Arm Player 1
        if (input().down(Gosu::KB_W)) {
            if (!swordPlayer1.upKeyPressed) {
                swordPlayer1.swordPosition = (swordPlayer1.swordPosition - 1 + 3) % 3; // Armposition nach oben wechseln
                swordPlayer1.upKeyPressed = true;
            }
        }
        else {
            swordPlayer1.upKeyPressed = false;
        }

        if (input().down(Gosu::KB_S)) {
            if (!swordPlayer1.downKeyPressed) {
                swordPlayer1.swordPosition = (swordPlayer1.swordPosition + 1) % 3; // Armposition nach unten wechseln
                swordPlayer1.downKeyPressed = true;
            }
        }
        else {
            swordPlayer1.downKeyPressed = false;
        }

        // Bewegung Arm Player 2
        if (input().down(Gosu::KB_UP)) {
            if (!swordPlayer2.upKeyPressed) {
                swordPlayer2.swordPosition = (swordPlayer2.swordPosition - 1 + 3) % 3; // Armposition nach oben wechseln
                swordPlayer2.upKeyPressed = true;
            }
        }
        else {
            swordPlayer2.upKeyPressed = false;
        }

        if (input().down(Gosu::KB_DOWN)) {
            if (!swordPlayer2.downKeyPressed) {
                swordPlayer2.swordPosition = (swordPlayer2.swordPosition + 1) % 3; // Armposition nach unten wechseln
                swordPlayer2.downKeyPressed = true;
            }
        }
        else {
            swordPlayer2.downKeyPressed = false;
        }

        // Player 1 Stich- & Ruheposition mit Cooldown (Funktioniert semi gut)
        if (input().down(Gosu::KB_SPACE)) {
            if (!swordPlayer1.extendingSword && (Gosu::milliseconds() > swordPlayer1.cooldown + 1000)) {
                swordPlayer1.cooldown = Gosu::milliseconds();
                swordPlayer1.extendingSword = true;
            }
        }
        else {
            swordPlayer1.extendingSword = false;
        }

        // Player 2 Stich- & Ruheposition mit Cooldown (Funktioniert semi gut)
        if (input().down(Gosu::KB_RETURN)) {
            if (!swordPlayer2.extendingSword && (Gosu::milliseconds() > swordPlayer2.cooldown + 1000)) {
                swordPlayer2.cooldown = Gosu::milliseconds();
                swordPlayer2.extendingSword = true;
            }
        }
        else {
            swordPlayer2.extendingSword = false;
        }
    }
};


int main() {
   GameWindow window;
   window.show();
   return 0;
}
