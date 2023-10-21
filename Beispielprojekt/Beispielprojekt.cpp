#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <cmath>
#include<iostream>

class Player {
public:
    double x, y;      
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
    }
};

class Sword {
public:
    int swordPosition;
    bool upKeyPressed;
    bool downKeyPressed;
    bool extendingSword;
    
    Sword(int, bool, bool, bool)
        : swordPosition(), upKeyPressed(), downKeyPressed(), extendingSword()
    {}
};


class GameWindow : public Gosu::Window
{
public:
    GameWindow()
        : Window(1920, 1080) { // Größe des Fensters
        set_caption("Nidhogg Fake");
         
    }

    Player player1 = Player(300, 540, false, false); // Startposition des ersten Spielers
    Player player2 = Player(1620, 540, false, false); // Startposition des zweiten Spielers
    Sword swordPlayer1 = Sword(0, false, false, false);     //Schwertposition des ersten Spielers
    Sword swordPlayer2 = Sword(0, false, false, false);    //Schwertposition des zweiten Spielers

    int steps = 50;                                 //Dynamische Variable fuer die Schrittweite
    int steps_divider = 5;                          //Dynamische Variable fuer mehrere Schritte

    void draw() override {
        Gosu::Font(24).draw_text("Nidhogg Fake", 860, 300, 0, 1, 1);

        //Player 1 Angriffsposition
        // Kopf
       if (swordPlayer1.extendingSword == true)
       {
            drawCircle(player1.x, player1.y, 25, Gosu::Color::GREEN);

            // Körper
            graphics().draw_line(player1.x, player1.y + 25, Gosu::Color::GREEN,
                player1.x -20, player1.y + 100, Gosu::Color::GREEN,
                0.0);
            // Schwertarm
            if (swordPlayer1.swordPosition == 2) {
                //Oben
                graphics().draw_line(player1.x -10, player1.y + 50, Gosu::Color::GREEN,
                    player1.x + 40, player1.y + 75, Gosu::Color::GREEN,
                    0.0);
                //Schwert
                graphics().draw_line(player1.x + 40, player1.y + 75, Gosu::Color::BLUE,
                    player1.x + 80, player1.y + 75, Gosu::Color::BLUE,
                    0.0);
                graphics().draw_line(player1.x + 45, player1.y + 85, Gosu::Color::BLUE,
                    player1.x + 45, player1.y + 65, Gosu::Color::BLUE,
                    0.0);
            }
            else if (swordPlayer1.swordPosition == 1) {
                //Mitte
                graphics().draw_line(player1.x-10, player1.y + 50, Gosu::Color::GREEN,
                    player1.x + 40, player1.y + 50, Gosu::Color::GREEN,
                    0.0);
                //Schwert
                graphics().draw_line(player1.x + 40, player1.y + 50, Gosu::Color::BLUE,
                    player1.x + 80, player1.y + 50, Gosu::Color::BLUE,
                    0.0);
                graphics().draw_line(player1.x + 45, player1.y + 60, Gosu::Color::BLUE,
                    player1.x + 45, player1.y + 40, Gosu::Color::BLUE,
                    0.0);
            }
            else if (swordPlayer1.swordPosition == 0) {
                //Unten
                graphics().draw_line(player1.x -10, player1.y + 50, Gosu::Color::GREEN,
                    player1.x + 40, player1.y + 25, Gosu::Color::GREEN,
                    0.0);
                //Schwert
                graphics().draw_line(player1.x + 40, player1.y + 25, Gosu::Color::BLUE,
                    player1.x + 80, player1.y + 25, Gosu::Color::BLUE,
                    0.0);
                graphics().draw_line(player1.x + 45, player1.y + 35, Gosu::Color::BLUE,
                    player1.x + 45, player1.y + 15, Gosu::Color::BLUE,
                    0.0);
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
                    player1.x + 55, player1.y + 75, Gosu::Color::BLUE,
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
                    player1.x + 55, player1.y + 50, Gosu::Color::BLUE,
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
                    player1.x + 55, player1.y + 25, Gosu::Color::BLUE,
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
                   player2.x - 80, player2.y + 75, Gosu::Color::BLUE,
                   0.0);
               graphics().draw_line(player2.x - 45, player2.y + 85, Gosu::Color::BLUE,
                   player2.x - 45, player2.y + 65, Gosu::Color::BLUE,
                   0.0);
           }
           else  if (swordPlayer2.swordPosition == 1) {
               //Mitte
               graphics().draw_line(player2.x + 10, player2.y + 50, Gosu::Color::WHITE,
                   player2.x - 40, player2.y + 50, Gosu::Color::WHITE,
                   0.0);
               //Schwert
               graphics().draw_line(player2.x - 40, player2.y + 50, Gosu::Color::BLUE,
                   player2.x - 80, player2.y + 50, Gosu::Color::BLUE,
                   0.0);
               graphics().draw_line(player2.x - 45, player2.y + 60, Gosu::Color::BLUE,
                   player2.x - 45, player2.y + 40, Gosu::Color::BLUE,
                   0.0);
           }
           else if (swordPlayer2.swordPosition == 0) {
               //Oben
               graphics().draw_line(player2.x + 10, player2.y + 50, Gosu::Color::WHITE,
                   player2.x - 40, player2.y + 25, Gosu::Color::WHITE,
                   0.0);
               //Schwert
               graphics().draw_line(player2.x - 40, player2.y + 25, Gosu::Color::BLUE,
                   player2.x - 80, player2.y + 25, Gosu::Color::BLUE,
                   0.0);
               graphics().draw_line(player2.x - 45, player2.y + 35, Gosu::Color::BLUE,
                   player2.x - 45, player2.y + 15, Gosu::Color::BLUE,
                   0.0);
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
                   player2.x - 55, player2.y + 75, Gosu::Color::BLUE,
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
                   player2.x - 55, player2.y + 50, Gosu::Color::BLUE,
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
                   player2.x - 55, player2.y + 25, Gosu::Color::BLUE,
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
                player1.move(-steps/steps_divider);
            }
        }
        else
        {
            player1.leftKeyPressed = false;
            player1.keyHold_l = 0;
        }

        if (input().down(Gosu::KB_D)) {
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

       if (input().down(Gosu::KB_LEFT)) {
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

        // Player 1 Stich- & Ruheposition
        if (input().down(Gosu::KB_SPACE)) {
            if (!swordPlayer1.extendingSword) {
                swordPlayer1.extendingSword = true;
            }
        }
        else {
            swordPlayer1.extendingSword = false;
        }

        // Player 2 Stich- & Ruheposition
        if (input().down(Gosu::KB_RETURN)) {
            if (!swordPlayer2.extendingSword) {
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
