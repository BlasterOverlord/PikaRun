#define width 1100
#define height 674
#define button_width 405
#define button_height 120
#define gamestate_limit 3
#define pikachu_x_coordinate 300
#define max_jump_limit 400
#define jumping_speed 30
#define music_counter 3
#define enemy_count 4
#define pikachu_width 80
#define pikachu_height 40
#define pokeball_height 70
#define name_limit 50

// Global variables
int mposx = 200, mposy = 173, dx = 5, dy = 5;
int exitz = -1, hover = -1, gamestate = -1;
int pikachuRunIndex = 0, pikachuJumpIndex = 0;
int pikachu_y_coordinate = 100;
bool musicOn = true;
bool jumping = false, jumpingUp = false;
int musicTracker = 0;
int score = 0;
char scoreString[12];
int pokeballX, pokeballY, pokeballIndex = 0;
int pokeballCount = 0;
int enemySpeed = 10;
int thunderboltIndex = 0, timeWaste = 0;
bool powerup = false;
bool playing = false;
int nameIndex = 0, readIndex = 0;
FILE *fp;

// Strings containing paths to files
char button[3][30] = { "images\\buttons\\play1.bmp", "images\\buttons\\score.bmp", "images\\buttons\\ins.bmp" };
char button2[3][30] = { "", "", "" };
char homemenu[30] = "images\\menu\\42_02.bmp";
char play[30] = "images\\menu\\play.bmp";
char highscore[30] = "images\\menu\\hs.bmp";
char ins[30] = "images\\menu\\idk05.bmp";
char exitButtonImg[30] = "images\\buttons\\exit.bmp";
char pikachuRun[4][30] = { "images\\pikachu\\run1.bmp", "images\\pikachu\\run2.bmp", "images\\pikachu\\run3.bmp", "images\\pikachu\\run4.bmp" };
char pikachuJump[5][30] = { "images\\pikachu\\jump1.bmp", "images\\pikachu\\jump2.bmp", "images\\pikachu\\jump3.bmp", "images\\pikachu\\jump4.bmp", "images\\pikachu\\jump5.bmp" };
char music[music_counter][50] = { "music\\pokemon.wav", "music\\PokemonWorld.wav", "music\\champion.wav" };
char pokeballs[9][30] = { "images\\pokeballs\\1.bmp", "images\\pokeballs\\2.bmp", "images\\pokeballs\\3.bmp", "images\\pokeballs\\4.bmp", "images\\pokeballs\\5.bmp", "images\\pokeballs\\6.bmp", "images\\pokeballs\\7.bmp", "images\\pokeballs\\8.bmp", "images\\pokeballs\\9.bmp", };
char box[30] = "images\\pokeballs\\box.bmp";
char balls[30] = "images\\pokeballs\\ball.bmp";
char gameover[30] = "images\\gameover.bmp";
char thunderbolt[3][40] = { "images\\thunderbolt\\1.bmp", "images\\thunderbolt\\2.bmp", "images\\thunderbolt\\3.bmp"};
char nameScreen[30] = "images\\name.bmp";
char name[name_limit];

//obstacles
struct obstacles {
	int x, y, index;
} enemy[enemy_count];

char rattata[6][30] = { "images\\obstacles\\rat\\1.bmp", "images\\obstacles\\rat\\2.bmp", "images\\obstacles\\rat\\3.bmp", "images\\obstacles\\rat\\4.bmp", "images\\obstacles\\rat\\5.bmp", "images\\obstacles\\rat\\6.bmp" };
char spearow[4][31] = { "images\\obstacles\\spearow\\1.bmp", "images\\obstacles\\spearow\\2.bmp", "images\\obstacles\\spearow\\3.bmp", "images\\obstacles\\spearow\\4.bmp" };
char meowth[5][30] = { "images\\obstacles\\meowth\\1.bmp", "images\\obstacles\\meowth\\2.bmp", "images\\obstacles\\meowth\\3.bmp", "images\\obstacles\\meowth\\4.bmp", "images\\obstacles\\meowth\\5.bmp" };
char balloon[30] = "images\\obstacles\\balloon.bmp";

/*
enemy[0] is rattata (common)
enemy[1] is spearow (common)
enemy[2] is meowth (rare)
enemy[3] is balloon (rare)
*/

struct highScore{
	char name[50], score[12];
} hs[10000];


char Background[70][30] = {
	"images\\plz\\image01.bmp",
	"images\\plz\\image02.bmp",
	"images\\plz\\image03.bmp",
	"images\\plz\\image04.bmp",
	"images\\plz\\image05.bmp",
	"images\\plz\\image06.bmp",
	"images\\plz\\image07.bmp",
	"images\\plz\\image08.bmp",
	"images\\plz\\image09.bmp",
	"images\\plz\\image10.bmp",
	"images\\plz\\image11.bmp",
	"images\\plz\\image12.bmp",
	"images\\plz\\image13.bmp",
	"images\\plz\\image14.bmp",
	"images\\plz\\image15.bmp",
	"images\\plz\\image16.bmp",
	"images\\plz\\image17.bmp",
	"images\\plz\\image18.bmp",
	"images\\plz\\image19.bmp",
	"images\\plz\\image20.bmp",
	"images\\plz\\image21.bmp",
	"images\\plz\\image22.bmp",
	"images\\plz\\image23.bmp",
	"images\\plz\\image24.bmp",
	"images\\plz\\image25.bmp",
	"images\\plz\\image26.bmp",
	"images\\plz\\image27.bmp",
	"images\\plz\\image28.bmp",
	"images\\plz\\image29.bmp",
	"images\\plz\\image30.bmp",
	"images\\plz\\image31.bmp",
	"images\\plz\\image32.bmp",
	"images\\plz\\image33.bmp",
	"images\\plz\\image34.bmp",
	"images\\plz\\image35.bmp",
	"images\\plz\\image36.bmp",
	"images\\plz\\image37.bmp",
	"images\\plz\\image38.bmp",
	"images\\plz\\image39.bmp",
	"images\\plz\\image40.bmp",
	"images\\plz\\image41.bmp",
	"images\\plz\\image42.bmp",
	"images\\plz\\image43.bmp",
	"images\\plz\\image44.bmp",
	"images\\plz\\image45.bmp",
	"images\\plz\\image46.bmp",
	"images\\plz\\image47.bmp",
	"images\\plz\\image48.bmp",
	"images\\plz\\image49.bmp",
	"images\\plz\\image50.bmp",
	"images\\plz\\image51.bmp",
	"images\\plz\\image52.bmp",
	"images\\plz\\image53.bmp",
	"images\\plz\\image54.bmp",
	"images\\plz\\image55.bmp",
	"images\\plz\\image56.bmp",
	"images\\plz\\image57.bmp",
	"images\\plz\\image58.bmp",
	"images\\plz\\image59.bmp",
	"images\\plz\\image60.bmp",
	"images\\plz\\image61.bmp",
	"images\\plz\\image62.bmp",
	"images\\plz\\image63.bmp",
	"images\\plz\\image64.bmp",
	"images\\plz\\image65.bmp",
	"images\\plz\\image66.bmp",
	"images\\plz\\image67.bmp",
	"images\\plz\\image68.bmp",
	"images\\plz\\image69.bmp",
	"images\\plz\\image69.bmp"

};