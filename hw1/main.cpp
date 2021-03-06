#include <iostream>
#include <string>
#include <vector>

using namespace std;

class States
{
private:
    string start;
    string goal;
    vector<string> result;
public:
    States(int);
    ~States();

    string& getStart();
    string& getGoal();
    vector<string>& getResult();
    void addToResult(string&);
    void removeFromResult();


    bool solution(string&);
    static string newMove(int, int, string&);
    static bool canMove(int, int, string&);
    static bool isNewMoveViable(int, int, string&);
    static int emptyPosition(string&);
    static void allMoves(string&, vector<string>&);
};

States::States(int size):result(0)
{
    result.reserve((size + 1) * (size + 1));
    string left(size,'>');
    string right(size,'<');

    start = left;
    start.append("_").append(right);

    goal = right;
    goal.append("_").append(left);
}

States::~States()
{
}

string& States::getStart()
{
    return start;
}

string& States::getGoal()
{
    return goal;
}

vector<string>& States::getResult()
{
    return result;
}

void States::addToResult(string& state)
{
    result.push_back(state);
}

void States::removeFromResult()
{
    result.pop_back();
}

bool States::solution(string& state)
{
    return state == this->goal;
}

string States::newMove(int index, int zeroPosition, string& state)
{
    string newState = state;
    swap(newState[index], newState[zeroPosition]);
    return newState;
}

bool States::canMove(int index, int zeroPosition, string& state)
{
    return (state[index] == '>' && (zeroPosition == index + 1 || zeroPosition == index + 2)) ||
           (state[index] == '<' && (zeroPosition == index - 1 || zeroPosition == index - 2));
}

bool States::isNewMoveViable(int index, int zeroPosition, string& state)
{
    swap(state[index], state[zeroPosition]);
    
    switch (zeroPosition)
    {
        case 0:
            return !((state[1] == state[2]) && (state[1] == '>'));
            break;
        case 1:
            return !((state[2] == state[3]) && (state[2] == '>'));
            break;
    
        default:
            if (zeroPosition == state.length() - 1) {
                return !((state[state.length() - 2] == state[state.length() - 3]) && (state[state.length() - 2] == '<'));
            }
            else if(zeroPosition == state.length() - 2) {
                return !((state[state.length() - 3] == state[state.length() - 4]) && (state[state.length() - 3] == '<'));
            }            
            break;
    }
    
    bool stuckInSameDirection = state[index - 2] == state[index - 1] &&
                               state[index + 2] == state[index + 1] &&
                               state[index - 2] == state[index + 2];

    bool stuckInBadJump = state[index + 2] == state[index - 1] &&
                         state[index - 2] == state[index + 1];
    
    return !(stuckInBadJump || stuckInSameDirection);
}

int States::emptyPosition(string& state)
{
    return state.find('_');
}

void States::allMoves(string& state, vector<string>& result)
{
    int len = state.length();
    int zeroPos = States::emptyPosition(state);
    
    int start = zeroPos - 2;
    int end = zeroPos + 2;

    string tmpState;;

    start = start >= 0 ? start : 0;
    end = end < len ? end : len - 1;

    for(size_t i = start; i <= end; i++)
    {
        tmpState = state;
        if (!(i == zeroPos) && States::canMove(i, zeroPos, tmpState))  
        {
            if (States::isNewMoveViable(i, zeroPos, tmpState)) 
            {
                result.push_back(tmpState);
            }
        }
    }
}

void printResult(vector<string>& states)
{    
    for(auto &state : states)
    {
        cout << state << endl;
    }
}

bool dfs(States& states, string& newState)
{
    states.addToResult(newState);
    
    if (states.solution(newState))
    {
        printResult(states.getResult());
        return true;
    }

    vector<string> newMoves;
    newMoves.reserve(4);
    States::allMoves(newState, newMoves);
    for(auto &move : newMoves)
    {
        if(dfs(states, move))
        {
            return true;
        }
    }

    states.removeFromResult();
    return false;
}

int main(int argc, char const *argv[])
{
    States states(atoi(argv[1]));
    dfs(states, states.getStart());
    return 0;
}
