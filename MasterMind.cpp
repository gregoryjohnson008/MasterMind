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
bool charWithinForAWithB(char* guess, string elem, int amountA, int amountB)
{
    for(int i = 0; i < 4; i++)
    {
        if(elem[i] == guess[i])
        {
            amountA--;
        }
        else
        {
            for(int j = 0; j < 4; j++) //Will delete if there are not exactly B out of place
            {
                if(elem[i] == guess[j])
                {
                    amountB--;
                }
            }
        }
    }
    return (amountA == 0 && amountB == 0);
}
// Expects valid input (non-null elem that contains a terminating character)
// Returns true if there is a corresponding character
// Ex: guess = 0123, if elem = 0156 returns true
//                   if elem = 5678 returns false
bool charInACorrPosWithB(char* guess, string elem, int amountB)
{
    for(int i = 0; i < 4; i++)
    {
        if(elem[i] == guess[i])
        {
            return true;
        }
        else
        {
            for(int j = 0; j < 4; j++) //Will delete if there are not exactly B out of place
            {
                if(elem[i] == guess[j])
                {
                    amountB--;
                }
            }
        }
    }
    return amountB != 0;
}

/*  Called to removes possible answers based on A and B
 *  1) If A > 0:
 *      1a) if B > 0: then delete nums that don't have A digits corresponding and another B digits from the guess
 *      1b) if B = 0: then delete nums that don't have exactly A digits corresponding
 *  2) If A = 0:
 *      2a) if B > 0: then delete all nums that have any of the digits in the corresponding position and don't have B of the digits
 *      2b) if B = 0: then delete all nums that have any of the digits
 *  Remove the guess
 */
void removeBasedOnResponse(char* guess, int A, int B)
{
    int removed = 0;
    // 1)
    if(A > 0)
    {
        for(int i = 0; i < posAnswers.size(); i++)
        {
            if(!charWithinForAWithB(guess, posAnswers[i], A, B)) // 1a) and 1b)
            {
                posAnswers.erase(posAnswers.begin()+i);
                i--;
                removed++;
            }
            else if(guess[0] == posAnswers[i][0] && guess[1] == posAnswers[i][1] && guess[2] == posAnswers[i][2] && guess[3] == posAnswers[i][3]) //Remove the guess
            {
                posAnswers.erase(posAnswers.begin()+i);
                i--;
                removed++;
            }
            
        }
    }
    else// 2)
    {
        for(int i = 0; i < posAnswers.size(); i++)
        {
            if(charInACorrPosWithB(guess, posAnswers[i], B)) // 2a) and 2b)
            {
                posAnswers.erase(posAnswers.begin()+i);
                i--;
                removed++;
            }
            else if(guess[0] == posAnswers[i][0] && guess[1] == posAnswers[i][1] && guess[2] == posAnswers[i][2] && guess[3] == posAnswers[i][3]) //Remove the guess
            {
                posAnswers.erase(posAnswers.begin()+i);
                i--;
                removed++;
            }
            
        }
    }
    //printf("Removed: %i\n", removed);
}

//Randomly retrieves next guess
void getNewGuess(char* guess)
{
    int getIndex = rand() % posAnswers.size();
    
    guess[0] = posAnswers[getIndex][0];
    guess[1] = posAnswers[getIndex][1];
    guess[2] = posAnswers[getIndex][2];
    guess[3] = posAnswers[getIndex][3];
    guess[4] = '\0';
}

int main(int argc, char *argv[])
{
	char answer[5];     //stores the actual answer
	answer[4] = '\0';
	
	char guess[5];      //stores the guess
	guess[4] = '\0';
	
    int buff[2];        //stores the A and B after guess is made
    
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
        int count = 1;
        do
        {
            //***********Gets new guess***********
            getNewGuess(guess);
            printf("Turn %i:\n", count);
            printf("answer: %s\n", answer);
            printf("guess: \t%s\n", guess);
            
            //***********Gets response***********
            getResponse(answer, guess, buff);
            printf("%iA %iB\n\n", buff[0], buff[1]);
            if(buff[0] == 4) {break;}
            //***********Removes from possible answers***********
            removeBasedOnResponse(guess, buff[0], buff[1]);
            //printAnswers();
        }
        while(count++ < 150);
        
        printf("Done in %i turns.\n", count);
        
	}
	
}

