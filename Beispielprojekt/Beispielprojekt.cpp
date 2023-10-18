#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <cmath>
#include<iostream>
/*
class GameWindow : public Gosu::Window
{
public:

	GameWindow()
		: Window(800, 600)
	{
		set_caption("Gosu Tutorial mit Git");
	}

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		graphics().draw_line(
			10, 20, Gosu::Color::RED,
			200, 100, Gosu::Color::GREEN,
			0.0
		);
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
*/


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
    
    Sword(int, bool, bool)
        : swordPosition(), upKeyPressed(), downKeyPressed()
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
    Sword swordPlayer1 = Sword(0, false, false);     //Schwertposition des ersten Spielers
    Sword swordPlayer2 = Sword(0, false, false);    //Schwertposition des zweiten Spielers

    int steps = 20;                                 //Dynamische Variable fuer die Schrittweite
    int steps_divider = 5;                          //Dynamische Variable fuer mehrere Schritte

    void draw() override {
        // Anzeige der Spielerpositionen auf dem Bildschirm
        //Gosu::draw_text("Spieler 1: x = " + std::to_string(player1.x) + ", y = " + std::to_string(player1.y), 10, 10, 0xFFFFFFFF);
        //Gosu::draw_text("Spieler 2: x = " + std::to_string(player2.x) + ", y = " + std::to_string(player2.y), 10, 30, 0xFFFFFFFF);
        Gosu::Font(24).draw_text("Nidhogg Fake", 860, 300, 0, 1, 1);
        
        /*
        graphics().draw_line(
            player1.x, player1.y, Gosu::Color::RED,
            player1.x, player1.y - 100, Gosu::Color::RED,
            0.0
        );

        graphics().draw_line(
            player2.x, player2.y, Gosu::Color::GREEN,
            player2.x, player2.y - 100, Gosu::Color::GREEN,
            0.0
        );
        */

        //Strichmännchen 1
        // Kopf
    
        drawCircle(player1.x, player1.y , 25, Gosu::Color::GREEN);

        // Körper
        graphics().draw_line(player1.x + player1.direction, player1.y +25, Gosu::Color::GREEN,
            player1.x + player1.direction, player1.y + 100, Gosu::Color::GREEN,
            0.0);  

        // Schwertarm 
        if (swordPlayer1.swordPosition == 2) {
            //Oben
            graphics().draw_line(player1.x + player1.direction, player1.y + 50, Gosu::Color::GREEN,
                player1.x + 30 + player1.direction, player1.y + 75, Gosu::Color::GREEN,
                0.0);
            //Schwert
            graphics().draw_line(player1.x + 30 + player1.direction, player1.y + 75, Gosu::Color::BLUE,
                player1.x + 70 + player1.direction, player1.y + 75, Gosu::Color::BLUE,
                0.0);
            graphics().draw_line(player1.x + 35 + player1.direction, player1.y + 85, Gosu::Color::BLUE,
                player1.x + 35 + player1.direction, player1.y + 65, Gosu::Color::BLUE,
                0.0);
        }
        else if (swordPlayer1.swordPosition == 1) {
            //Mitte
            graphics().draw_line(player1.x + player1.direction, player1.y + 50, Gosu::Color::GREEN,
                player1.x + 30 + player1.direction, player1.y + 50, Gosu::Color::GREEN,
                0.0);
            //Schwert
            graphics().draw_line(player1.x + 30 + player1.direction, player1.y + 50, Gosu::Color::BLUE,
                player1.x + 70 + player1.direction, player1.y + 50, Gosu::Color::BLUE,
                0.0);
            graphics().draw_line(player1.x + 35 + player1.direction, player1.y + 60, Gosu::Color::BLUE,
                player1.x + 35 + player1.direction, player1.y + 40, Gosu::Color::BLUE,
                0.0);
        }
        else if (swordPlayer1.swordPosition == 0) {
            //Unten
            graphics().draw_line(player1.x + player1.direction, player1.y + 50, Gosu::Color::GREEN,
                player1.x + 30 + player1.direction, player1.y + 25, Gosu::Color::GREEN,
                0.0);
            //Schwert
            graphics().draw_line(player1.x + 30 + player1.direction, player1.y + 25, Gosu::Color::BLUE,
                player1.x + 70 + player1.direction, player1.y + 25, Gosu::Color::BLUE,
                0.0);
            graphics().draw_line(player1.x + 35 + player1.direction, player1.y + 35, Gosu::Color::BLUE,
                player1.x + 35 + player1.direction, player1.y + 15, Gosu::Color::BLUE,
                0.0);
        }
        // linker Arm 
        graphics().draw_line(player1.x + player1.direction, player1.y + 50, Gosu::Color::GREEN,
            player1.x - 30 + player1.direction, player1.y + 50, Gosu::Color::GREEN,
            0.0);  
        graphics().draw_line(player1.x -30 + player1.direction, player1.y + 50, Gosu::Color::GREEN,
            player1.x + player1.direction, player1.y + 80, Gosu::Color::GREEN,
            0.0);

        // rechtes Bein
        graphics().draw_line(player1.x + player1.direction, player1.y + 100, Gosu::Color::GREEN,
            player1.x + 30 + player1.direction, player1.y + 120, Gosu::Color::GREEN,
            0.0);  

        // linkes Bein
        graphics().draw_line(player1.x + player1.direction, player1.y + 100, Gosu::Color::GREEN,
            player1.x - 30 + player1.direction, player1.y + 120, Gosu::Color::GREEN,
            0.0);  


        //Strichmännchen 2
        // Kopf
        
        drawCircle(player2.x, player2.y, 25, Gosu::Color::WHITE);


        // Körper 
        graphics().draw_line(player2.x, player2.y +25, Gosu::Color::WHITE,
            player2.x, player2.y + 100, Gosu::Color::WHITE,
            0.0);  

        // rechter Arm
        graphics().draw_line(player2.x, player2.y + 50, Gosu::Color::WHITE,
            player2.x + 30, player2.y + 50, Gosu::Color::WHITE,
            0.0);  
        graphics().draw_line(player2.x + 30, player2.y + 50, Gosu::Color::WHITE,
            player2.x, player2.y +80, Gosu::Color::WHITE,
            0.0);

        //Schwertarm 
        if (swordPlayer2.swordPosition == 2) {
            //Unten
            graphics().draw_line(player2.x + player2.direction, player2.y + 50, Gosu::Color::WHITE,
                player2.x - 30 + player2.direction, player2.y + 75, Gosu::Color::WHITE,
                0.0);
            //Schwert
            graphics().draw_line(player2.x - 30 + player2.direction, player2.y + 75, Gosu::Color::BLUE,
                player2.x - 70 + player2.direction, player2.y + 75, Gosu::Color::BLUE,
                0.0);
            graphics().draw_line(player2.x - 35 + player2.direction, player2.y + 85, Gosu::Color::BLUE,
                player2.x - 35 + player2.direction, player2.y + 65, Gosu::Color::BLUE,
                0.0);
        }
        else  if (swordPlayer2.swordPosition == 1) {
            //Mitte
            graphics().draw_line(player2.x, player2.y + 50, Gosu::Color::WHITE,
                player2.x - 30, player2.y + 50, Gosu::Color::WHITE,
                0.0);
            //Schwert
            graphics().draw_line(player2.x - 30 + player2.direction, player2.y + 50, Gosu::Color::BLUE,
                player2.x - 70 + player2.direction, player2.y + 50, Gosu::Color::BLUE,
                0.0);
            graphics().draw_line(player2.x - 35 + player2.direction, player2.y + 60, Gosu::Color::BLUE,
                player2.x - 35 + player2.direction, player2.y + 40, Gosu::Color::BLUE,
                0.0);
        }
        else if (swordPlayer2.swordPosition == 0) {
            //Oben
            graphics().draw_line(player2.x + player2.direction, player2.y + 50, Gosu::Color::WHITE,
                player2.x - 30 + player2.direction, player2.y + 25, Gosu::Color::WHITE,
                0.0);
            //Schwert
            graphics().draw_line(player2.x - 30 + player2.direction, player2.y + 25, Gosu::Color::BLUE,
                player2.x - 70 + player2.direction, player2.y + 25, Gosu::Color::BLUE,
                0.0);
            graphics().draw_line(player2.x - 35 + player2.direction, player2.y + 35, Gosu::Color::BLUE,
                player2.x - 35 + player2.direction, player2.y + 15, Gosu::Color::BLUE,
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
        // Steuerung für Spieler 1

        //Alter Code
        /* 
        if (input().down(Gosu::KB_A))
        {
            if (!player1.leftKeyPressed && !input().down(Gosu::KB_A))
            {
                //player1.direction = -3; // Links
                player1.move(-3);
                player1.leftKeyPressed = true;
            }
            else if (player1.leftKeyPressed && !input().down(Gosu::KB_A))
            {
                player1.leftKeyPressed = false;
            }
        }
        
        else if (input().down(Gosu::KB_D))
        {
            if (!player1.rightKeyPressed)
            {
                //player1.direction = -3; // Links
                player1.move(3);
                player1.rightKeyPressed = true;
            }
            else
            {
                player1.rightKeyPressed = false;
            }
        }
        else 
        {
            player1.direction = 0; // Keine Bewegung
        }
       */
        
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
        
    }
    /*
    private:
        Player player1(100, 300);
       // Player player2(100, 300);
    */
};


int main() {
   GameWindow window;
   window.show();
   return 0;
}
