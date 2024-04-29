#include <iostream>
#include <vector>
#include <list>

int gcd(int a, int b) {
    int r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a; 
}

class Fraction{
    int numerator;
    int denominator;
    public:
    Fraction(int num,int denom){
        bool flag_neg=false;
        if ((num<0 && denom>0)||(num>0 && denom<0)){
            flag_neg=true;
        }
        numerator=std::abs(num);
        denominator=std::abs(denom);
        int gcd=::gcd(numerator,denominator);
        numerator/=gcd;
        denominator/=gcd;
        if (numerator==0) denominator=0;
        if (flag_neg) numerator=-numerator;
    }
    Fraction(double decimal) {
        int local_denominator = 1;
        bool flag_neg=false;
        if(decimal<0) flag_neg=true;
        decimal=std::abs(decimal);
        while(decimal != static_cast<int>(decimal)) {
            decimal *= 10;
            local_denominator *= 10;
        }
        int local_numerator = static_cast<int>(decimal);
        int gcd = ::gcd(local_numerator, local_denominator);
        
        numerator = local_numerator / gcd;
        denominator = local_denominator / gcd;
        if (flag_neg) {
            numerator = -numerator;
        }
        if (numerator==0) denominator=0;
    }

    Fraction  operator+(Fraction & obj) const{
        return Fraction(numerator*obj.denominator+obj.numerator*denominator,denominator*obj.denominator);
    }
    Fraction  operator-(Fraction & obj) const{
        return Fraction(numerator*obj.denominator-obj.numerator*denominator,denominator*obj.denominator);
    }
    Fraction operator*(Fraction & obj) const{
        return Fraction(numerator*obj.numerator,denominator*obj.denominator);
    }
    friend std::ostream& operator << (std::ostream& os, const Fraction& obj) {
        os << obj.numerator << "/" << obj.denominator<<' ';
        return os;
    }
    bool operator==(const Fraction& other) const {
        if(denominator==other.denominator && numerator==other.numerator){
            return true;
        }
        return false;
    }
    operator double() const{
        return numerator/static_cast<double>(denominator);
    }
    int hash_code() const{
        if ((numerator^denominator)<0){
            return -numerator^denominator;
        }
        return numerator^denominator;

    }

};


class Hashset{
    int count;
    int size;
    std::vector<std::list<Fraction> > buckets;
public:
    Hashset(){
        count=0;
        size=5; 
        buckets.resize(5);
    }
    void add(const Fraction & obj){
        int hash_code=obj.hash_code();
        if(!contains(obj)){
            count++;
            if (count==size){
                int new_size=size*2;
                std::vector<std::list<Fraction> > bucket_new(new_size);
                for (int i=0;i!=size-1;i++){
                    std::list<Fraction> a=buckets[i];
                    for(std::list<Fraction>::iterator j=a.begin();j!=a.end();j++){
                        bucket_new[(*j).hash_code()%new_size].push_back(*j);
                    }
                }
                size=new_size;
                buckets.clear();
                buckets=bucket_new;
                bucket_new.clear();
            }
            buckets[hash_code%size].push_back(obj);
        }
    }   
    bool contains(const Fraction & obj){
        int index=obj.hash_code()%size;
        for(std::list<Fraction>::iterator j=buckets[index].begin();j!=buckets[index].end();j++){
            if(*j==obj){return true;}
        }
        return false;
    }
    void remove(const Fraction & obj){
        int index=obj.hash_code()%size;
        for(std::list<Fraction>::iterator j=buckets[index].begin();j!=buckets[index].end();j++){
            if(j!=buckets[index].end() && *j==obj){
                buckets[index].erase(j);
                count--;
                return;
            }
        }
    }
};




int main(){
    


}
