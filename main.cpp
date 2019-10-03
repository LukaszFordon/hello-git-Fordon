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
 float speed;
 public:

    Paddle (){
         rectangle_.setSize(sf::Vector2f(60.0, 60.0));
         rectangle_.setPosition(500.0, 400.0);
         rectangle_.setFillColor(sf::Color(255, 255, 255));
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


    void step(float delta_x)
    {
        float stepp=0.5;
        rectangle_.move(stepp*delta_x,0);
        //usunięcie nadmiarowych if
    }
    void set_speed(float v)
    {
        speed=v;
    }
    float get_speed()
    {
        return speed;
    }
};

class Shot{

protected:
 sf::RectangleShape shot_;
 public:

    Shot (){
         shot_.setSize(sf::Vector2f(10.0, 10.0));
         shot_.setPosition(500.0, 500.0);
         shot_.setFillColor(sf::Color(100, 0, 0));
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
    void up(float delta_y)
    {
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

    void step(float delta_x)
    {
        float stepp=0.5;
        shot_.move(stepp*delta_x,0);
    }
};

using namespace std;

Paddle ustawienia(vector<Paddle> &rectangles )
{

    for(auto it=rectangles.begin();it!=rectangles.end();it++)
    {
        it->set_position(((std::rand() % 750 ) + 0.0f),30.0f);
        it->set_speed(((std::rand() % 10 )/20.0f) + 0.4f);
    }
    return rectangles[0];
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
    int lap=0;
    float plane_x;
    float plane_y;

    sf::Texture meteor;
    meteor.loadFromFile("bomba.png");
    sf::Sprite kometa;
    kometa.setTexture(meteor);

    sf::Texture serce;
    serce.loadFromFile("serce.png");
    sf::Sprite hp;
    hp.setTexture(serce);

    sf::Texture gracz;
    gracz.loadFromFile("samolot.png");
    sf::Sprite samolot;
    samolot.setTexture(gracz);

    sf::Texture tekstura;
    tekstura.loadFromFile( "niebo.jpg" );
    sf::Sprite obrazek;
    obrazek.setTexture( tekstura );

    int zycie=3;
    vector<Paddle> life;
    for (int i=0;i<zycie;i++) {
        Paddle tmp;
        tmp.set_size(50,50);
        tmp.set_position(i*60,100);

        life.push_back(tmp);
    }
    if(zycie>=0)
    {
    cout<<"LIFE: "<<zycie<<endl;
    }

    int pociski=0;
    //cout<<"SHOTS: "<<pociski<<endl;
    srand( time( NULL ) );
    bool b=false;
    bool up=false;

    std::vector<Paddle> rectangles;
    std::vector<Shot*> strzaly;
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    Paddle rectangle_1;
    rectangle_1.set_position(400,600);
    rectangle_1.bounds(plane_x,plane_y);
    Shot pocisk_1;
    pocisk_1.set_position(424,630);

    for(int i=0;i<=40;i++)
    {
        Paddle rec;
        rectangles.push_back(rec);
    }
    ustawienia(rectangles);


    Paddle rectangle_d;
    rectangle_d.set_position(0,700);
    rectangle_d.set_size(8000,5);
    Paddle rectangle_u;
    rectangle_u.set_size(8000,5);
    rectangle_u.set_position(0,10);
    Paddle rectangle_r;
    rectangle_r.set_position(800,550);
    rectangle_r.set_size(5,200);
    Paddle rectangle_l;
    rectangle_l.set_position(-5,550);
    rectangle_l.set_size(5,200);


    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    sf::Clock clock;
 while (window.isOpen()) {
     float delta;
     do{
     delta= float(clock.getElapsedTime().asSeconds());
     //cout<<delta<<endl;
     }while(delta<0.007f);

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
    pocisk_1.set_position(plane_x+24,630);
}

    for(auto it=rectangles.begin();it!=rectangles.begin()+10+2*lap;it++)
    {
    // cout<<speed<<endl;
     it->down(it->get_speed());
    }

    for(auto it=rectangles.begin();it!=rectangles.begin()+10+2*lap;it++)
    {
        if(rectangle_1.doKolizji().intersects(it->doKolizji()))
        {
            it->set_position(100,1000);
            if(zycie>0)
            {
            zycie--;
            }
            cout<<"LIFE:"<<zycie<<endl;
         }
        if(pocisk_1.doKolizji().intersects(it->doKolizji()))
        {
            it->set_position(100,1000);
        }
    }

    plane_x=polozenie(rectangle_1);


    if(rectangle_1.doKolizji().intersects(rectangle_r.doKolizji())==true )
    {
    //cout<<"trafiony";
    rectangle_1.step(-2.0);
    pocisk_1.step(-2.0);
    }
    if(rectangle_1.doKolizji().intersects(rectangle_l.doKolizji())==true )
    {
    //cout<<"trafiony";
    rectangle_1.step(2.0);
    pocisk_1.step(2.0);
    }
      obrazek.setScale(0.44f,0.46f);
      window.draw( obrazek );//tlo

      //rectangle_1.draw(window);
      samolot.setPosition(plane_x,plane_y);
      samolot.setScale(0.085f, 0.085f);//
      window.draw(samolot);

      for(auto it=life.begin();it!=life.begin()+zycie;it++)
      {
          float xs,ys;
          it->bounds(xs,ys);
          //it->draw(window);
          hp.setPosition(xs,ys);
          hp.setScale(0.03f, 0.03f);//
          window.draw(hp);
      }

      rectangle_d.draw(window);
      rectangle_u.draw(window);
      rectangle_r.draw(window);
      rectangle_l.draw(window);

       pocisk_1.draw(window);

       for(auto itr=rectangles.begin(); itr!=rectangles.begin()+10+2*lap;itr++)
       {
        //itr->draw(window);
        float xs,ys;
        itr->bounds(xs,ys);
        kometa.setPosition(xs-20,ys-20);
        kometa.setScale(0.059f, 0.06f);
        window.draw(kometa);

       }

       for(auto itr_2=strzaly.begin(); itr_2!=strzaly.end();itr_2++)
       {
        (*itr_2)->draw(window);
       }

       if(zycie<=0)
       {
        cout<<"YOU LOST !"<<endl;
        window.close();
       }
       int i=0;
       for(auto it=rectangles.begin();it!=rectangles.end();it++)
       {
           if(collision_d(rectangle_d,(*it))==true)
               i++;
       }

       if(i>=10+2*lap)
    {
        lap++;
        pociski=1;
        //cout<<"SHOTS: "<<pociski<<endl;
        if(zycie>0)
        {
            ustawienia(rectangles);

        }
    }

    if(lap==15)
    {
    window.close();
    cout<<"YOU WIN !!!"<<endl;
    }

   window.display();
}
    return 0;
}
