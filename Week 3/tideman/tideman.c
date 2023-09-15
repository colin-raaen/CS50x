#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
bool visited[MAX];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool DPS_cycle_check(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Compare vote name with candidate name
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // if name matches candidate, add preference to rank array
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // for every rank
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // compare to other ranks
        for (int j = 0; j < n; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // traverse 2d array preferences array
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            //compare preferences values and update pairs array
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // set swap counter to non-zero number
    int swap_counter = -1;
    // continue bubble sorting until swap counter equals 0
    while (swap_counter != 0)
    {
        //set or reset swap counter to 0
        swap_counter = 0;
        pair buffer;
        //loop through pairs array comparing magnitude of win
        for (int i = 0, n = pair_count; i < n - 1; i++)
        {
            //bubble pairs if in wrong order
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                buffer = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = buffer;
                swap_counter++;
            }
        }

    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop through pairs to record values in locked array
    for (int i = 0, n = pair_count; i < n; i++)
    {
        //reset visited array for every DFS cycle check
        for (int j = 0; j < n; j++)
        {
            visited[j] = false;
        }

        // call cycle check FDS function, record locked pair if cycle doesn't exist
        if (DPS_cycle_check(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

//check for cycles
bool DPS_cycle_check(int winner, int loser)
{
    //set loser vertex as visited
    visited[loser] = true;
    // loop through pairs
    for (int i = 0; i < candidate_count; i++)
    {
        //base case if back edge is detected (i.e. if current winner has been defeated, and defeater has been visited)
        if (locked[i][winner] == true && (visited[i] == true))
        {
            //return cycle exists
            return true;
        }
        //recursive case, winner has lost but doesn't have a back edge, keep checking in stack until winner hasn't been defeated
        else if (locked[i][winner] == true && visited[i] == false)
        {
            //call recursive function with current winner as loser, and winner's defeater as winner
            return DPS_cycle_check(i, winner);
        }
    }
    //return cycle doesn't exist, no back edge detected
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    //loop through 2day array
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //if candidate has been defeated, can't be winner, not source of graph
            if (locked[j][i] == true)
            {
                break;
            }
            //case when candidate hasn't been defeated, source of graph, print winner and exit
            if (j == (candidate_count - 1) && locked[j][i] == false)
            {
                printf("%s\n", candidates[i]);
                return;
            }
        }
    }
    return;
}
