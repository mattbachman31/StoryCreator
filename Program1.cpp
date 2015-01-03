#include "Story.h"
#include <fstream>

using namespace std;

int main()
{
	char filename1[] = "Gilligan.txt";
	char filename2[] = "240testout.txt";
	char filename3[] = "FreshPrince.txt";
	Story myStory1(filename1);
	++myStory1;
	--myStory1;
	myStory1.save(filename2);
	myStory1 = Story(filename2);
	myStory1++;
	myStory1--;
	Story myStory2(filename3);
	Story myStory4;
	cout << myStory1 << endl;
	cout << "===============" << endl;
	myStory4 = myStory1 + 1; 
	cout << myStory1 << endl;
	myStory4--;
	cout << "===============" << endl;
	cout << myStory4 << endl;
	myStory4 = myStory4 + 1;
	cout << "===============" << endl;
	cout << myStory4 << endl;
	Story myStory3 = myStory1 + myStory2;
	Story myStory5 = myStory4;
	
	Word w1, w2, w3, w4, w5(w4), w6=w5;
	   Sentence s1, s2, s3, s4, s5(s4), s6=s5;
	   Paragraph p1, p2, p3(p2), p4=p3;
	   Story st1, st2, st3(st2), st4=st3;
	   w1++;
	   w1--;
	   --w1;
	   ++w1;
	   w2 = w1 + 1;
	   s1++;
	   s1--;
	   ++s1;
	   --s1;
	   s2 = s1 + w1; 
	   s1 = w1 + w2 + w3; 
	   s2 = w2 + w4;
	   p1 = (s1 + s2);
	   p2 = p1 + 1;
	   st1 = st1 + p2 + ((p1 + p1 + p1) + 1);
	   /*char one[] = "hi";
	   char two[] = "there";
	   char three[] = "everyone.";
	   Word wone = Word(one, ((sizeof(one)/sizeof(one[0])))-1);
	   Word wtwo = Word(two, ((sizeof(two)/sizeof(two[0])))-1);
	   Word wthree = Word(three, ((sizeof(three)/sizeof(three[0])))-1);
	   Word warr[] = {wone, wtwo, wthree};
	   Sentence sen1 = Sentence(warr, 3);
	   Sentence sen2 = Sentence(warr, 3);
	   Sentence sen3 = Sentence(warr, 3);
	   Sentence sen4 = Sentence(warr, 3);
	   cout << sen1 << " " << sen2 << " " << sen3 << " " << sen4 << endl;
	   cout << sen3 << endl;
	   Sentence sarr1[] = {sen1,sen2};
	   Sentence sarr2[] = {sen3,sen4};
	   Paragraph par1(sarr1,2);
	   Paragraph par2(sarr2,2);
	   cout << par1 << " " << par2 << endl;
	   Story thisStory = par1 + par2;
	   cout << thisStory << endl;
	   thisStory++;
	   cout << thisStory << endl;
	   thisStory--;
	   cout << thisStory << endl;
	   ++thisStory;
	   cout << thisStory << endl;
	   --thisStory;
	   cout << thisStory << endl;
	   Story copyStory = thisStory;
	   cout << copyStory << endl;*/
	return 0;
}
