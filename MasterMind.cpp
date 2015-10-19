#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> posAnswers;   //array of all possible combinations

//prints descriptions of expected input
void printArgReq()
{
    printf("Argument is incorrect.\n");
    printf("Takes one argument that is a four digit number without repeating digits.\n");
}

//prints possible answers array
void printAnswers()
{
    int count = 0;
    for(int i = 0; i < posAnswers.size(); i++)
    {
        if(posAnswers[i][0] != 'n')
        {
            if(count % 20 == 0)
            {
                printf("\n");
            }
            cout << posAnswers.at(i) << " ";
            count++;
        }
    }
    printf("\ncount: %i\n", count);
}

//Input checking to ensure that there are no duplicate digits in the answer
bool isRepeat(char* input)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = i + 1; j < 4; j++)
		{
			if(input[i] == input[j])
			{
				return true;
			}
		}
	}
	return false;
}

//Populates the all possible answers array
void populatePossibilities()
{
    int ind = 0;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            for(int k = 0; k < 10; k++)
            {
                for(int l = 0; l < 10; l++)
                {
                    if(i != j && i != k && i != l && j != k && j != l && k != l)
                    {
                        string toPush = ("");
                        toPush += i + '0';
                        toPush += j + '0';
                        toPush += k + '0';
                        toPush += l + '0';
                        posAnswers.push_back(toPush);
                        ind++;
                    }
                }
            }
        }
    }
}

//Figures out the A and B values to respond to the guess with
void getResponse(char* answer, char* guess, int* buff)
{
    //buff[A, B] = [in correct position, in answer somewhere but not in right position]
    buff[0] = 0;
    buff[1] = 0;
    
    int nums[10] = {0,0,0,0,0,0,0,0,0,0};
    
    for(int i = 0; i < 4; i++)
    {
        if(answer[i] == guess[i])
        {
            buff[0]++;
            nums[guess[i] - '0'] = 1; //the index corresponds to having that number ( > 1 )
        }
    }
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(answer[i] == guess[j] && nums[guess[j] - '0'] == 0)
            {
                buff[1]++;
                nums[guess[j] - '0'] = 1;
            }
        }
    }
}

//Fills the guess
void getNextGuess(char* guess)
{
    
}

// Expects valid input (non-null elem that contains a terminating character)
// Returns true if the elem has the digits in the right position amount times
// Ex: guess = 0123, if elem = 0156 and amount = 2 returns true
//                   if elem = 0156 and amount = 3 returns false
bool charNWithinForA(char* guess, string elem, int amount)
{
    int ind = 0;
    const char* element = elem.c_str();

    while(ind < 4)
    {
        if(element[ind] == guess[ind])
        {
            amount--;
        }
        ind++;
    }
    return amount <= 0;
}
/*  Called when the A value is greater than 0.
 *  1) Removes the numbers in the array that does not have any of the guess digits in a corresponding positions (Ex: guess = 1234, removes nums that don't have 1 in the first spot or 2 in the 2nd spot...)
 */
void removeAGreaterThanZero(char* guess, int A)
{
    // 1)
    for(int i = 0; i < posAnswers.size(); i++)
    {
        if(!charNWithinForA(guess, posAnswers[i], A)) //Remove if does not have any of the numbers
        {
            posAnswers.erase(posAnswers.begin()+i);
            i--;
        }
        else if(guess[0] == posAnswers[i][0] && guess[1] == posAnswers[i][1] && guess[2] == posAnswers[i][2] && guess[3] == posAnswers[i][3]) //Remove the guess
        {
            posAnswers.erase(posAnswers.begin()+i);
            i--;
        }
        
    }
}


int main(int argc, char *argv[]) 
{
	char answer[5];     //stores the actual answer
	answer[4] = '\0';
	
	char guess[5];      //stores the guess
	guess[4] = '\0';
	strncpy(guess, "0123", 4);
	
    int buff[2];        //stores the A and B after guess is made
    buff[0] = 0;
    buff[1] = 1;
    
    populatePossibilities(); //fills array of possible answers
    
	if(argc != 2  || strnlen(argv[1], 6) != 4)  //there must be input and its length must be 4
	{
		printArgReq();
		return 0;
	}
    
	strncpy(answer, argv[1], 4);
	printf("answer: %s\n", answer);
	
	if(isRepeat(answer))    //can not have a repeating digit
	{
		printArgReq();
		return 0;
	}
	else 
	{
        int count = 0;
        /*do
        {
            printf("guess: \t%s\n", guess);
            getResponse(answer, guess, buff);
            printf("%iA %iB\n", buff[0], buff[1]);
        }while(buff[0] != 4 && ++count < 100);  */
        
        printf("guess: \t%s\n", guess);
        getResponse(answer, guess, buff);
        printf("%iA %iB\n", buff[0], buff[1]);
        removeAGreaterThanZero(guess, buff[0]);
        printAnswers();
        
	}
	
}

