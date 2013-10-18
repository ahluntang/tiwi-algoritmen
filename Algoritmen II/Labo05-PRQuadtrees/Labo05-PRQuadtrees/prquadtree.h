#ifndef __QUADTREE
#define __QUADTREE
//Quadtree voor punten met int-co"ordinaten
//de PRquadtree kan alleen punten bevatten met
//-maxcoordinaat <= x < maxcoordinaat
//-maxcoordinaat <= y < maxcoordinaat
const int OOST=0;
const int WEST=1;
const int NOORD=0;
const int ZUID=2;

class Gebied{
public:
    Gebied(int maxc):xl(-maxc),xr(maxc),yl(-maxc),yr(maxc),xc(0),yc(0){};
    void maakdeelgebied(int x,int y){
        if (x<xc)
            xr=xc;
        else
            xl=xc;
        if (y<yc)
            yr=yc;
        else
            yl=yc;
        xc=(xl+xr)/2;
        yc=(yl+yr)/2;
    };
    int geefKwadrant(int x, int y) const{
        return (x<xc ? WEST : OOST) + (y<yc? NOORD: ZUID);
    }
    
private:
    int xl,xr,yl,yr,xc,yc;//geven grenzen gebied; l,r,c: links, rechts, centraal.
};

class PRquadtree{
public:
    PRquadtree(int _maxcoordinaat):maxcoordinaat(_maxcoordinaat),k(0){};
    //voegtoe veronderstelt dat het punt in het gebied ligt.
    void voegtoe(int x,int y);
    void print(){
        Knoop** huidig = &k;
    }
protected:
    class Knoop{
    public:
        virtual bool isblad() const =0;
    };
    class Blad:public Knoop{
    public:
        Blad(int _x,int _y):x(_x),y(_y){};
        virtual bool isblad() const { return true;}
        int x,y;//co"ordinaten punt
    };
    class Nietblad:public Knoop{
        friend class PRquadtree;
    public:
        Nietblad(){
            for (int i=0; i<4; i++ )
                kind[i]=0;
        }
        virtual bool isblad() const{ return false;}
    private:
        static const int OOST, WEST, NOORD, ZUID;
        Knoop* kind[4];//indexeren met windrichting (bv. kind[NOORD+WEST] bevat punten
        //met x en y kleiner dan grenswaarde)
        //leeg gebied: nulpointer
    };
    const int maxcoordinaat;//wordt opgegeven in constructor;
    Knoop* k;
    
};
const int PRquadtree::Nietblad::OOST=OOST;
const int PRquadtree::Nietblad::WEST=WEST;
const int PRquadtree::Nietblad::NOORD=NOORD;
const int PRquadtree::Nietblad::ZUID=ZUID;

void PRquadtree::voegtoe(int x, int y){
    if (x > maxcoordinaat || x < -maxcoordinaat || y > maxcoordinaat || y < -maxcoordinaat) {
        return;
    }
    Gebied g(maxcoordinaat);
    
    Knoop** huidig=&k;
    while(*huidig!=0){
        if((*huidig)->isblad()){
            Blad* blad =(Blad*) *huidig;
            if (x == blad->x && y == blad->y){
                return;
            }
            *huidig = new Nietblad();
            ((Nietblad*) *huidig)->kind[g.geefKwadrant(blad->x,blad->y)] = blad;
        }
        huidig = &(((Nietblad*) *huidig)->kind[g.geefKwadrant(x,y)]);
        g.maakdeelgebied(x,y);
    }
    
    *huidig=new Blad(x,y);
}



#endif

