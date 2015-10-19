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

// Expects valid input (non-null elem that contains a terminating character)
// Returns true if the elem has the digits in the right position amount times
// Ex: guess = 0123, if elem = 0156 and amount = 2 returns true
//                   if elem = 0156 and amount = 3 returns false
bool charNWithinForA(char* guess, string elem, int amount)
{
    for(int i = 0; i < 4; i++)
    {
        if(elem[i] == guess[i])
        {
            amount--;
        }
    }
    return amount <= 0;
}
// Expects valid input (non-null elem that contains a terminating character)
// Returns true if there is a corresponding character
// Ex: guess = 0123, if elem = 0156 returns true
//                   if elem = 5678 returns false
bool charInACorrPos(char* guess, string elem)
{
    for(int i = 0; i < 4; i++)
    {
        if(elem[i] == guess[i])
        {
            return true;
        }
    }
    return false;
}

/*  Called when the A value is greater than 0.
 *  1) Removes the numbers in the array that does not have any of the guess digits in a corresponding positions (Ex: guess = 1234, removes nums that don't have 1 in the first spot or 2 in the 2nd spot...)
 *  2) If A = 0 then delete all nums that have any of the digits in the corresponding position
 */
void removeBasedOnA(char* guess, int A)
{
    // 1)
    if(A > 0)
    {
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
    else// 2)
    {
        for(int i = 0; i < posAnswers.size(); i++)
        {
            if(charInACorrPos(guess, posAnswers[i])) //Remove if a character corresponds
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
	
	if(isRepeat(answer))    //can not have a repeating digit
	{
		printArgReq();
		return 0;
	}
	else 
	{
        int count = 0;
        do
        {
            printf("answer: %s\n", answer);
            printf("guess: \t%s\n", guess);
            getResponse(answer, guess, buff);
            printf("%iA %iB\n", buff[0], buff[1]);
            removeBasedOnA(guess, buff[0]);
            printAnswers();
            guess[0] = posAnswers[0][0];
            guess[1] = posAnswers[0][1];
            guess[2] = posAnswers[0][2];
            guess[3] = posAnswers[0][3];
            guess[4] = '\0';
        }while(buff[0] != 4 && ++count < 150);
        
        printf("Done in %i turns.\n", count);
        
	}
	
}

