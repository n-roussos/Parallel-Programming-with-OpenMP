#define ALPHA (double) 0.001

#define NUM_TRAIN 600000

#define L1_NEURONS 100
#define L2_NEURONS 10

#define PIXELS (28*28)
#define L1_DIM (PIXELS+1)
#define L2_DIM (L1_NEURONS+1)

//desired activation values
#define ACTIVATION_VALUE_FALSE 0.1
#define ACTIVATION_VALUE_TRUE 0.9

//**********************************

#define TRAIN_EXAMPLES 60000
#define TEST_EXAMPLES 10000

#define BUFFER_SIZE 4000

#define MAX_PIXEL_VALUE (double) 255.0


double WL1[L1_NEURONS][L1_DIM];
double WL2[L2_NEURONS][L2_DIM];

double DL1[L1_NEURONS];
double DL2[L2_NEURONS];

double OL1[L1_NEURONS];
double OL2[L2_NEURONS];

double DELTA_L1[L1_NEURONS];
double DELTA_L2[L2_NEURONS];

//*****************************************************

const char *TRAINSET_PATH = "fashion-mnist_train.csv";
const char *TESTSET_PATH = "fashion-mnist_test.csv";

double TRAIN_DATA[TRAIN_EXAMPLES][PIXELS]; //bigger memory, but no conversion from unsigned char to double is needed
double TRAIN_B[TRAIN_EXAMPLES][L2_NEURONS];	//train desired
unsigned char TRAIN_CLASS[TRAIN_EXAMPLES];


double TEST_DATA[TEST_EXAMPLES][PIXELS]; //bigger memory, but no conversion from unsigned char to double is needed
unsigned char TEST_CLASS[TEST_EXAMPLES];
