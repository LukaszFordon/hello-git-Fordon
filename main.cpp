#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Paddle{
protected:
 sf::RectangleShape rectangle_;
 public:
    Paddle (){
        rectangle_.setSize(sf::Vector2f(60.0, 60.0));
        rectangle_.setPosition(500.0, 400.0);
        rectangle_.setFillColor(sf::Color(255, 10, 10));
        rectangle_.getGlobalBounds();
      }

    void bounds(float x, float y)
    {
        y=rectangle_.getGlobalBounds().top;
        x=rectangle_.getGlobalBounds().left;
    }
    void draw(sf::RenderWindow &w)
    {
       w.draw(rectangle_);

    }
    void down(float delta_y){
        rectangle_.move(0,1*delta_y);
    }


    void set_position(float x, float y){
        rectangle_.setPosition(x-100,y-100);

    }
    void step(float delta_x){
                double stepp=0.3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            rectangle_.move(stepp*delta_x,0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            rectangle_.move(stepp*delta_x,0);
        }
    }
};


using namespace std;

int main()
{
     sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    Paddle rectangle_1;
    rectangle_1.set_position(200,600);
    Paddle rectangle_2;
    rectangle_2.set_position(500,100);
    Paddle rectangle_3;
    rectangle_3.set_position(300,100);
    Paddle rectangle_4;
    rectangle_4.set_position(200,100);
    Paddle rectangle_5;
    rectangle_5.set_position(550,100);
    Paddle rectangle_6;

    sf::Texture tekstura;
    tekstura.loadFromFile( "niebo.jpg" );
    sf::Sprite obrazek;
    obrazek.setTexture( tekstura );



    sf::Clock clock;
 while (window.isOpen()) {
     float delta= float(clock.getElapsedTime().asSeconds());
     clock.restart();

     sf::Event event;
     while (window.pollEvent(event)) {
         // "close requested" event: we close the window
         if (event.type == sf::Event::Closed)
             window.close();
     }
      window.clear(sf::Color::Black);
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                      rectangle_1.step(-2.0);
                  }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                      rectangle_1.step(2.0);
                  }
    rectangle_2.down(0.5);
    rectangle_3.down(1);
    rectangle_4.down(0.75);
    rectangle_5.down(0.2);
    float x1;
    float y1;
    float x2;
    float y2;
     rectangle_1.bounds(x1,y1);
     rectangle_2.bounds(x2,y2);

     cout<<x1<<endl;
     cout<<x2<<endl;
      window.draw( obrazek );

    rectangle_1.draw(window);
    rectangle_2.draw(window);
    rectangle_3.draw(window);
    rectangle_4.draw(window);
    rectangle_5.draw(window);
   window.display();
}
    return 0;
}
