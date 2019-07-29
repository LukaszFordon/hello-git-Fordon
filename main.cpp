#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include<vector>
#include <cstdlib>
#include <ctime>

class Paddle{

protected:
 sf::RectangleShape rectangle_;
 public:

    Paddle (){
         rectangle_.setSize(sf::Vector2f(60.0, 60.0));
         rectangle_.setPosition(500.0, 400.0);
         rectangle_.setFillColor(sf::Color(255, 255, 10));
         rectangle_.getGlobalBounds();

      }

    void bounds(float &x, float &y)
    {
        y=rectangle_.getGlobalBounds().top;
        x=rectangle_.getGlobalBounds().left;
    }
    void draw(sf::RenderWindow &w)
    {
       w.draw(rectangle_);

    }
    void down(float delta_y){
        rectangle_.move(0,2*delta_y);
    }

    void set_size(float x, float y)
    {
        rectangle_.setSize(sf::Vector2f(x,y));
    }


    void set_position(float x, float y){
        rectangle_.setPosition(x,y-100);

    }

    sf::FloatRect doKolizji()
    {
        return rectangle_.getGlobalBounds();
    }
    int get_x()
    {
        sf::Vector2f pos=rectangle_.getPosition();
        return pos.x;
    }
    int get_y()
    {
        sf::Vector2f pos = rectangle_.getPosition();
        return pos.y;
    }


    void step(float delta_x){
                double stepp=0.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            rectangle_.move(stepp*delta_x,0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            rectangle_.move(stepp*delta_x,0);
        }
        else {
           rectangle_.move(stepp*delta_x,0);
        }
    }
};

class Shot{

protected:
 sf::RectangleShape shot_;
 public:

    Shot (){
         shot_.setSize(sf::Vector2f(10.0, 10.0));
         shot_.setPosition(500.0, 500.0);
         shot_.setFillColor(sf::Color(155, 255, 10));
         shot_.getGlobalBounds();


      }

    void bounds(float &x, float &y)
    {
        y=shot_.getGlobalBounds().top;
        x=shot_.getGlobalBounds().left;
    }
    void draw(sf::RenderWindow &w)
    {
       w.draw(shot_);

    }
    void up(float delta_y){
        shot_.move(0,2*delta_y);
    }

    void set_size(float x, float y)
    {
        shot_.setSize(sf::Vector2f(x,y));
    }


    void set_position(float x, float y){
        shot_.setPosition(x,y-100);

    }

    sf::FloatRect doKolizji()
    {
        return shot_.getGlobalBounds();
    }

    void step(float delta_x){
                double stepp=0.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            shot_.move(stepp*delta_x,0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            shot_.move(stepp*delta_x,0);
        }
    }
};

using namespace std;

Paddle ustawienia(Paddle &rectangle_2, Paddle &rectangle_3, Paddle &rectangle_4, Paddle &rectangle_5,Paddle &rectangle_6,Paddle &rectangle_7,Paddle &rectangle_8 )
{
    int x2=( std::rand() % 750 ) + 0;
    int x3 =( std::rand() % 750 ) + 0;
    int x4=( std::rand() % 750 ) + 0;
    int x5 =( std::rand() % 750 ) + 0;
    int x6=( std::rand() % 650 ) + 200;
    int x7=( std::rand() % 750 ) + 0;
    int x8=( std::rand() % 450 ) + 200;

    rectangle_2.set_position(x2,30);
    rectangle_3.set_position(x3,30);
    rectangle_4.set_position(x4,30);
    rectangle_5.set_position(x5,30);
    rectangle_6.set_position(x6,30);
    rectangle_7.set_position(x7,30);
    rectangle_8.set_position(x8,30);
    return rectangle_2;

}

bool collision(Paddle &rectangle_A, Paddle &rectangle_B)
{
        float x1;
        float y1;
        float x2;
        float y2;
        rectangle_A.bounds(x1, y1);
        rectangle_B.bounds(x2, y2);

        //cout << x1 << " : " << y1 << endl;
        //cout << x2 << " : " << y2 << endl;

        if (x1 + 50 > x2 && x1 - 50 < x2 && y1 + 50 > y2 && y1 - 50 < y2)
        {
                cout << "=====" << endl;
                return true;
        }
        return false;
}

bool collision_d(Paddle &rectangle_A, Paddle &rectangle_B)
{
        float x1;
        float y1;
        float x2;
        float y2;
        rectangle_A.bounds(x1, y1);
        rectangle_B.bounds(x2, y2);

       // cout << x1 << " : " << y1 << endl;
       //cout << x2 << " : " << y2 << endl;

        if (y1  < y2 )
        {
                //cout << "/////" << endl;
                return true;
        }
        return false;
}

float polozenie(Paddle &rectangle_A)
{
    float plane_x;
    float plane_y;
    rectangle_A.bounds(plane_x,plane_y);
    //cout<<plane_x<<endl;
    return plane_x;
}

bool shotcollision(Shot &rectangle_A, Paddle &rectangle_B)
{
        float x1;
        float y1;
        float x2;
        float y2;
        rectangle_A.bounds(x1, y1);
        rectangle_B.bounds(x2, y2);

        //cout << x1 << " : " << y1 << endl;
        //cout << x2 << " : " << y2 << endl;

        if (x1 + 50 > x2 && x1 - 50 < x2 && y1 + 50 > y2 && y1 - 50 < y2)
        {
                cout << "+++++++" << endl;
                return true;
        }
        return false;
}

int main()
{
    float plane_x;
    float plane_y;

    int zycie=3;
    cout<<"LIFE: "<<zycie<<endl;
    int pociski=0;
    //cout<<"SHOTS: "<<pociski<<endl;
    srand( time( NULL ) );
    bool b=false;
    bool up=false;
    sf::Texture texture;
    texture.loadFromFile("samolot.jpg");

    sf::Sprite sprite;
    sprite.setTexture(texture);

    std::vector<Paddle*> runda;
    std::vector<Shot*> strzaly;
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    Paddle rectangle_1;
    rectangle_1.set_position(400,600);
    rectangle_1.bounds(plane_x,plane_y);
    Shot pocisk_1;
    pocisk_1.set_position(420,630);

    Paddle rectangle_2;
    Paddle rectangle_3;
    Paddle rectangle_4;
    Paddle rectangle_5;
    Paddle rectangle_6;
    Paddle rectangle_7;
    Paddle rectangle_8;
    ustawienia(rectangle_2, rectangle_3,rectangle_4,rectangle_5,rectangle_6,rectangle_7,rectangle_8);
    runda.push_back(&rectangle_2);
    runda.push_back(&rectangle_3);
    runda.push_back(&rectangle_4);
    runda.push_back(&rectangle_5);
    runda.push_back(&rectangle_6);
    runda.push_back(&rectangle_7);
    runda.push_back(&rectangle_8);
    Paddle rectangle_d;
    rectangle_d.set_position(0,700);
    rectangle_d.set_size(8000,5);
    Paddle rectangle_u;
    rectangle_u.set_size(8000,5);
    rectangle_u.set_position(0,10);


    sf::Texture tekstura;
    tekstura.loadFromFile( "niebo.jpg" );
    sf::Sprite obrazek;
    obrazek.setTexture( tekstura );

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

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

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
                      rectangle_1.step(-2.0);
                    if(!b)
                    {
                     pocisk_1.step(-2.0);
                    }

      }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
                    rectangle_1.step(2.0);

                    if(!b )
                    {
                     pocisk_1.step(2.0);
                    }
       }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
         b=true;
         pociski=0;
               }

if(b==true)
{
    pocisk_1.up(-0.5);
}
if(pocisk_1.doKolizji().intersects(rectangle_u.doKolizji())==true )
{
    up=true;
}

if(b==true && pociski>0 && up==true)
{
    pocisk_1.set_position(plane_x+25,630);
}

    rectangle_2.down(0.5);
    rectangle_3.down(0.75);
    rectangle_4.down(0.75);
    rectangle_5.down(0.4);
    rectangle_6.down(( std::rand() % 1 ) + 0.4);
    rectangle_7.down(( std::rand() % 3 ) + 0.4);
    rectangle_8.down(( std::rand() % 2 ) + 0.4);

    if(rectangle_1.doKolizji().intersects(rectangle_2.doKolizji())==true )
    {
    zycie--;
    cout<<"LIFE: "<<zycie<<endl;
    rectangle_2.set_position(100,1000);
    }
    if(rectangle_1.doKolizji().intersects(rectangle_3.doKolizji())==true )
    {
    zycie--;
    cout<<"LIFE: "<<zycie<<endl;
    rectangle_3.set_position(100,1000);
    }
    if(rectangle_1.doKolizji().intersects(rectangle_4.doKolizji())==true )
    {
    zycie--;
    cout<<"LIFE: "<<zycie<<endl;
    rectangle_4.set_position(100,1000);
    }
    if(rectangle_1.doKolizji().intersects(rectangle_5.doKolizji())==true )
    {
    zycie--;
    cout<<"LIFE: "<<zycie<<endl;
    rectangle_5.set_position(100,1000);
    }
    if(rectangle_1.doKolizji().intersects(rectangle_6.doKolizji())==true )
    {
    zycie--;
    cout<<"LIFE: "<<zycie<<endl;
    rectangle_6.set_position(100,1000);
    }
    if(rectangle_1.doKolizji().intersects(rectangle_7.doKolizji())==true )
    {
    zycie--;
    cout<<"LIFE: "<<zycie<<endl;
    rectangle_7.set_position(100,1000);
    }
    if(rectangle_1.doKolizji().intersects(rectangle_8.doKolizji())==true )
    {
    zycie--;
    cout<<"LIFE: "<<zycie<<endl;
    rectangle_8.set_position(100,1000);
    }
       // collision(rectangle_1, rectangle_2);
     //   collision(rectangle_1, rectangle_3);
       // collision(rectangle_1, rectangle_4);
       // collision(rectangle_1, rectangle_5);
       // collision(rectangle_1, rectangle_6);
      //  collision(rectangle_1, rectangle_7);
       // collision(rectangle_1, rectangle_8);

    plane_x=polozenie(rectangle_1);
    if(pocisk_1.doKolizji().intersects(rectangle_2.doKolizji())==true )
    {
    //cout<<"trafiony";
    rectangle_2.set_position(100,1000);
    }

    if(pocisk_1.doKolizji().intersects(rectangle_3.doKolizji())==true )
    {
   // cout<<"trafiony";
    rectangle_3.set_position(100,1000);
    }
    if(pocisk_1.doKolizji().intersects(rectangle_4.doKolizji())==true )
    {
   // cout<<"trafiony";
    rectangle_4.set_position(100,1000);
    }
    if(pocisk_1.doKolizji().intersects(rectangle_5.doKolizji())==true )
    {
    //cout<<"trafiony";
    rectangle_5.set_position(100,1000);
    }
    if(pocisk_1.doKolizji().intersects(rectangle_6.doKolizji())==true )
    {
    //cout<<"trafiony";
    rectangle_6.set_position(100,1000);
    }
    if(pocisk_1.doKolizji().intersects(rectangle_7.doKolizji())==true )
    {
    //cout<<"trafiony";
    rectangle_7.set_position(100,1000);
    }
    if(pocisk_1.doKolizji().intersects(rectangle_8.doKolizji())==true )
    {
    //cout<<"trafiony";
    rectangle_8.set_position(100,1000);
    }

      window.draw( obrazek );//tlo
      rectangle_1.draw(window);
      sf::Texture gracz;
      gracz.loadFromFile("samolot.jpg");
      sf::Sprite samolot;
      samolot.setTexture(gracz);
      int x, y;
      x = rectangle_1.get_x();
      y = rectangle_1.get_y();
      samolot.setPosition(plane_x,plane_y);
      samolot.setScale(1.0, 1.0);//
      window.draw(samolot);




      rectangle_d.draw(window);
      rectangle_u.draw(window);

       pocisk_1.draw(window);
       for(auto itr=runda.begin(); itr!=runda.end();itr++)
       {
        (*itr)->draw(window);
       }

       for(auto itr_2=strzaly.begin(); itr_2!=strzaly.end();itr_2++)
       {
        (*itr_2)->draw(window);
       }

       int i=0;
       if(collision_d(rectangle_d, rectangle_8)==true)
        i++;
       if(collision_d(rectangle_d, rectangle_7)==true)
        i++;
       if(collision_d(rectangle_d, rectangle_6)==true)
        i++;
       if(collision_d(rectangle_d, rectangle_5)==true)
        i++;
       if(collision_d(rectangle_d, rectangle_4)==true)

        i++;
       if(collision_d(rectangle_d, rectangle_3)==true)
        i++;
       if(collision_d(rectangle_d, rectangle_2)==true)
        i++;

       if(i==7)
    {
           pociski=1;
           cout<<"SHOTS: "<<pociski<<endl;
           if(zycie>0)
           {
        ustawienia(rectangle_2, rectangle_3,rectangle_4,rectangle_5,rectangle_6,rectangle_7,rectangle_8);


        for(auto itr=runda.begin(); itr!=runda.end();itr++)
        {
         (*itr)->draw(window);
          i=2;
        }
            }
           else
           {
            cout<<"PRZEGRALES !"<<endl;
            window.close();
           }

    }





   window.display();
}
    return 0;
}
