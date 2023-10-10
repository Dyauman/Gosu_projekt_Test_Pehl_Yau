#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
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
    int direction; // 1 für rechts, -1 für links

    Player(double startX, double startY)
        : x(startX), y(startY), direction(1) {
    }

    void move(double speed) {
        x += speed * direction;
    }
};

class GameWindow : public Gosu::Window
{
public:
    GameWindow()
        : Window(1280, 720) { // Größe des Fensters
        set_caption("Nidhogg Fake");
        }
    
    Player player1 = Player(300, 350); // Startposition des ersten Spielers
    Player player2 = Player(700, 350); // Startposition des zweiten Spielers

    void draw() override {
        // Anzeige der Spielerpositionen auf dem Bildschirm
        //Gosu::draw_text("Spieler 1: x = " + std::to_string(player1.x) + ", y = " + std::to_string(player1.y), 10, 10, 0xFFFFFFFF);
        //Gosu::draw_text("Spieler 2: x = " + std::to_string(player2.x) + ", y = " + std::to_string(player2.y), 10, 30, 0xFFFFFFFF);
        Gosu::Font(24).draw_text("const std::string & text", 400, 300, 0,1,1);

        graphics().draw_line(
            player1.x, player1.y, Gosu::Color::RED,
            200, 100, Gosu::Color::GREEN,
            0.0
        );
        graphics().draw_line(
            player2.x, player2.y, Gosu::Color::RED,
            200, 100, Gosu::Color::GREEN,
            0.0
        );
    }
/*
    void update() override {
        // Steuerung für Spieler 1
        if (input().down(Gosu::KB_A)) {
            player1.direction = -1; // Links
        }
        else if (input().down(Gosu::KB_D)) {
            player1.direction = 1; // Rechts
        }
        else {
            player1.direction = 0; // Keine Bewegung
        }

        // Steuerung für Spieler 2
        if (input().down(Gosu::KB_LEFT)) {
            player2.direction = -1; // Links
        }
        else if (input().down(Gosu::KB_RIGHT)) {
            player2.direction = 1; // Rechts
        }
        else {
            player2.direction = 0; // Keine Bewegung
        }

        // Bewegung der Spieler
        player1.move(2.0);
        player2.move(2.0);
    }

private:
    Player player2(100, 300);
    Player player2(100, 300);
};
*/
};

int main() {
   GameWindow window;
   window.show();
   return 0;
}
