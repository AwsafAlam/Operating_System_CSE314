
class Cake
{
private:
    /* data */
    int id;
    int type;
public:
    Cake(int id, int type);
    int getID(){return id;}
    int getType(){return type;}
};

Cake::Cake(int i, int t)
{
    id = i;
    type = t;
}