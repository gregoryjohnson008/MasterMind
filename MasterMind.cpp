#include <iostream>

using namespace std;

int* getResponse(char* answer, char* guess)
{
	int ret[2]; //[in correct position, in answer somewhere but not in right position]
	ret[0] = 0;
	ret[1] = 0;
	
	int nums[10] = {0,0,0,0,0,0,0,0,0,0};
	
	for(int i = 0; i < 4; i++)
	{
		if(answer[i] == guess[i])
		{
			ret[0]++;
			nums[guess[i] - '0'] = 1; //the index corresponds to having that number ( > 1 )
		}		
	}
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(answer[i] == guess[j] && nums[guess[j] - '0'] == 0)
			{
				ret[1]++;
				nums[guess[j] - '0'] = 1;
			}
		}
	}
	
	return ret;
}

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

void printArgReq()
{
	printf("Argument is incorrect.\n");
	printf("Takes one argument that is a four digit number without repeating digits.");
}

int main(int argc, char *argv[]) 
{
	//Feed actual answer
	//program makes guess and is fed response until it finds the correct 		answer
	
	char posAnswers[5040][5];
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
						posAnswers[ind][0] = i + '0';
						posAnswers[ind][1] = j + '0';
						posAnswers[ind][2] = k + '0';
						posAnswers[ind][3] = l + '0';
						posAnswers[ind][4] = '\0';
						
						ind++;
					}
				}
			}
		}
	}
	
	char answer[5];
	answer[4] = '\0';
	
	char guess[5];
	guess[4] = '\0';
	strncpy(guess, "0000", 4);
	
	if(argc != 2)
	{
		printArgReq();
		return 0;
	}
	
	strncpy(answer, argv[1], 4);
	printf("answer: %s\n", answer);
	printf("guess: \t%s\n", guess);
	
	if(isRepeat(answer))
	{
		printArgReq();
		return 0;
	}
	else 
	{
		int *nums = getResponse(answer, guess);
		printf("%iA %iB", nums[0], nums[1]);
	}
	
}

