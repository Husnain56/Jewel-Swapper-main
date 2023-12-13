//MUAZ 23L-0816
//HUSNAIN 23L-0860

#include<iostream>
#include<SFML\Graphics.hpp>
#include<fstream>

using namespace std;
using namespace sf;

////////////////////////////////////////////////////////////////////////////////////////////////////////
// SWAP FUNCT

void swaper(int &a, int &b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BLAST FUNCTIONS

void destroyerBlast(int arr[8][8], int i, int j, int& score) {
	for (int row = 0; row < 8; row++) {
		for (int col = j; col < 8; col++) {
			for (int k = i - 1; k >= 0; k--) {
				arr[k + 1][col] = arr[k][col];
			}
		}
	arr[row][j] = rand() % 5 + 1;
	}	
	for (int col = j; col < 8; col++) {
		arr[0][col] = rand() % 5 + 1;
	}
	score += 200;

}

void powerBlast(int arr[8][8], int i, int j , int &score) {
	if (arr[i][j] > 5) {
		for (int row = i + 1; row <= i + 1; row++) {
			for (int col = j - 1; col <= j + 1; col++) {
				for (int k = row - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 1][j + 1] = arr[k][j + 1];
					arr[k + 1][j + 2] = arr[k][j + 2];
				}
				arr[0][j] = rand() % 5 + 1;
				arr[0][j + 1] = rand() % 5 + 1;
				arr[0][j + 2] = rand() % 5 + 1;
			}
		}
	}
	score += 100;
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ELIGIBLE SWAP CHECKER

void canSwap(int& a, int& b, int arr[8][8], bool &swap) {
	 swap = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			if ((arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2]) ||
				(arr[i][j] - 5 == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2]) || 
				(arr[i][j] == arr[i][j + 1] - 5 && arr[i][j + 1] - 5 == arr[i][j + 2]) || 
				(arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] - 5) || 
				(arr[i][j] - 10 == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2]) || 
				(arr[i][j] == arr[i][j + 1] - 10 && arr[i][j + 1] - 10 == arr[i][j + 2]) ||
				(arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] - 10) || 
				(arr[i][j] > 5 && (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] + 5)) ||
				(arr[i][j] > 5 && (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] + 5 == arr[i][j + 2] + 5))) {
				swap = true;
			}
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			if ((arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j]) || 
				(arr[i][j] - 5 == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j]) || 
				(arr[i][j] == arr[i + 1][j] - 5 && arr[i + 1][j] - 5 == arr[i + 2][j]) ||
				(arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] - 5) || 
				(arr[i][j] - 10 == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j]) ||
				(arr[i][j] == arr[i + 1][j] - 10 && arr[i + 1][j] - 10 == arr[i + 2][j]) ||
				(arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] - 10) || 
				(arr[i][j] > 5 && (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] + 5)) ||
				(arr[i][j] > 5 && (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] + 5 == arr[i][j + 2] + 5))) {
				swap = true;
			}
		}
	}
	if (!swap) {
		swaper(a, b);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// SCORE DISPLAY WINDOW

void scoreWindow(int score) {
	/////////////////////////////////////////////////////////////////////////////////
	// WINDOW

	RenderWindow scorewindow(VideoMode(1200, 800), "Bejeweled Blitz");

	/////////////////////////////////////////////////////////////////////////////////
	// FONT

	Font font;
	if (!font.loadFromFile("RubikMonoOne-Regular.ttf")) {}


	/////////////////////////////////////////////////////////////////////////////////
	// TEXT

	Text scoreText;

	scoreText.setFont(font);
	scoreText.setString("Your Score is " + to_string(score));
	scoreText.setCharacterSize(50);
	scoreText.setPosition(250, 250);
	scoreText.setFillColor(Color::White);

	int highscore = 0;

	ifstream infile;
	infile.open("highscore.txt");
	infile >> highscore;
	if (score > highscore) {
		highscore = score;
	}
	infile.close();
	Text highscoreText;

	highscoreText.setFont(font);
	highscoreText.setString("HighScore:" + to_string(highscore));
	highscoreText.setCharacterSize(50);
	highscoreText.setPosition(300, 350);
	highscoreText.setFillColor(Color::White);


	Clock timer;
	Time elapsedTime;
	Time timeLimit = seconds(10);

	ofstream outfile;
	outfile.open("highscore.txt", ios::out);
	outfile << highscore;
	outfile.close();
	//rename("temp.txt","highscore.txt" );
	while (scorewindow.isOpen()) {
		Event event;
		while (scorewindow.pollEvent(event)) {
			if (event.type == Event::Closed) {
				scorewindow.close();
			}
			else if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					scorewindow.close();
				}
			}
		}
		elapsedTime = timer.getElapsedTime();

		if (elapsedTime >= timeLimit) {
			scorewindow.close();
		}
		scorewindow.clear();
		scorewindow.draw(scoreText);

		scorewindow.draw(highscoreText);
		scorewindow.display();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME WINDOW

void playGame() {

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// WINDOW

	RenderWindow game(VideoMode(1200, 800), "Bejeweled Blitz");

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// BACKGROUND

	Texture gameBgTexture;
	if (!gameBgTexture.loadFromFile("gameBg.jpg")) {}

	Sprite gameBg;
	gameBg.setScale(1200.f / gameBgTexture.getSize().x, 800.f / gameBgTexture.getSize().y);
	gameBg.setTexture(gameBgTexture);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FONT

	Font font;
	if (!font.loadFromFile("RubikMonoOne-Regular.ttf")) {}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TEXT

	Text escText;

	escText.setFont(font);
	escText.setString("Press [Esc] to exit");
	escText.setCharacterSize(12);
	escText.setPosition(10, 10);
	escText.setFillColor(Color::White);


	Text controlsText;

	controlsText.setFont(font);
	controlsText.setString("Arrow keys to move cursor \n A S D W to swap");
	controlsText.setCharacterSize(12);
	controlsText.setPosition(10, 760);
	controlsText.setFillColor(Color::White);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TIMER

	Clock timer;
	Time elapsedTime;
	Time timeLimit = seconds(60);
	Text timeText;

	timeText.setFont(font);
	timeText.setString("Time");
	timeText.setCharacterSize(70);
	timeText.setPosition(100, 420);
	timeText.setFillColor(Color::Magenta);

	Text time;

	time.setFont(font);
	time.setCharacterSize(70);
	time.setPosition(120, 500);
	time.setFillColor(Color::White);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SCORE

	Text scoreText;

	scoreText.setFont(font);
	scoreText.setString("Score");
	scoreText.setCharacterSize(70);
	scoreText.setPosition(100, 200);
	scoreText.setFillColor(Color::Magenta);

	Text scoreDisplay;

	scoreDisplay.setFont(font);
	scoreDisplay.setCharacterSize(50);
	scoreDisplay.setPosition(100, 280);
	scoreDisplay.setFillColor(Color::White);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TABLE

	Texture tableTexture1;
	if (!tableTexture1.loadFromFile("table1.png")) {}

	Sprite table1;
	table1.setScale(70.f / tableTexture1.getSize().x, 70.f / tableTexture1.getSize().y);
	table1.setTexture(tableTexture1);


	Texture tableTexture2;
	if (!tableTexture2.loadFromFile("table2.png")) {}

	Sprite table2;
	table2.setScale(70.f / tableTexture2.getSize().x, 70.f / tableTexture2.getSize().y);
	table2.setTexture(tableTexture2);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// GEMS

	int arr[8][8] = {0};
	int random = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			random = rand() % 5 + 1;
			arr[i][j] = random;
		}
	}

	Texture gemTexture;
	Sprite gem;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SELECTOR

	Texture selectTexture;
	if (!selectTexture.loadFromFile("selected.png")) {}

	Sprite select;
	select.setScale(70.f / selectTexture.getSize().x, 70.f / selectTexture.getSize().y);
	select.setTexture(selectTexture);
	select.setPosition(540, 150);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MAIN LOOP

		int score = 0;
	while (game.isOpen()) {

		int i = 0, j = 0;
		bool swap = false;
		Event event;
		while (game.pollEvent(event)) {
			if (event.type == Event::Closed) {
				game.close();
			}
			else if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					game.close();
					scoreWindow(score);
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				// MOVEMENT

				else if (Keyboard::isKeyPressed(Keyboard::Down) && select.getPosition().y != 640) {
					select.move(0.f, +70.f);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) && select.getPosition().y != 150) {
					select.move(0.f, -70.f);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left) && select.getPosition().x != 540) {
					select.move(-70.f, 0.f);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && select.getPosition().x != 1030) {
					select.move(+70.f, 0.f);
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				// SWAPPING

				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				// DOWN

				else if (Keyboard::isKeyPressed(Keyboard::S) && select.getPosition().y != 640) {
					i = (select.getPosition().y - 150) / 70;
					j = (select.getPosition().x - 540) / 70;
					select.move(0.f, +70.f);
					swaper(arr[i][j], arr[i + 1][j]);
					canSwap(arr[i][j], arr[i + 1][j], arr, swap);
					if(!swap) { select.move(0.f, -70.f); }
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				// UP

				else if (Keyboard::isKeyPressed(Keyboard::W) && select.getPosition().y != 150) {
					i = (select.getPosition().y - 150) / 70;
					j = (select.getPosition().x - 540) / 70;
					select.move(0.f, -70.f);
					swaper(arr[i][j], arr[i - 1][j]);
					canSwap(arr[i][j], arr[i - 1][j], arr, swap);
					if (!swap) { select.move(0.f, +70.f); }
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				// LEFT

				else if (Keyboard::isKeyPressed(Keyboard::A) && select.getPosition().x != 540) {
					i = (select.getPosition().y - 150) / 70;
					j = (select.getPosition().x - 540) / 70;
					select.move(-70.f, 0.f);
					swaper(arr[i][j], arr[i][j - 1]);
					canSwap(arr[i][j], arr[i][j-1], arr, swap);
					if (!swap) { select.move(+70.f,0.f); }
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				// RIGHT

				else if (Keyboard::isKeyPressed(Keyboard::D) && select.getPosition().x != 1030) {
					i = (select.getPosition().y - 150) / 70;
					j = (select.getPosition().x - 540) / 70;
					select.move(+70.f, 0.f);
					swaper(arr[i][j], arr[i][j + 1]);
					canSwap(arr[i][j], arr[i][j+1], arr, swap);
					if (!swap) { select.move(-70.f, 0.f); }
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// TIMER

		elapsedTime = timer.getElapsedTime();

		if (elapsedTime >= timeLimit) {
			game.close();
			scoreWindow(score);
		}
		int timeLeft = 60 - elapsedTime.asSeconds();
		time.setString(to_string(timeLeft));
	

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// DRAW ELEMENTS

		game.clear();
		game.draw(gameBg);
		game.draw(escText);
		game.draw(controlsText);
		game.draw(timeText);
		game.draw(time);
		game.draw(scoreText);
	
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// TABLE

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
				table1.setPosition(540 + (70 * j), 150 + (70 * i));
				game.draw(table1);
			}
			else {
				table2.setPosition(540 + (70 * j), 150 + (70 * i));
				game.draw(table2);
			}

		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LOADING GEMS

	bool flag = true;
	while (flag) {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			gem.setPosition(540 + (70 * j), 150 + (70 * i));
			if (!gemTexture.loadFromFile("gem" + to_string(arr[i][j]) + ".png")) {}
			gem.setScale(70.f / gemTexture.getSize().x, 70.f / gemTexture.getSize().y);
			gem.setTexture(gemTexture);
			game.draw(gem);
		}
	}
	flag = false;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FOR DESTROYER GEM OF L SHAPE

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] && arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2]) {
				arr[i][j] += 10;
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 2][j] = arr[k + 1][j];
					arr[k + 3][j] = arr[k + 2][j];
				}
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j + 1] = arr[k][j + 1];
					arr[k + 1][j + 2] = arr[k][j + 2];
				}
				arr[0][j + 1] = rand() % 5 + 1;
				arr[0][j + 2] = rand() % 5 + 1;

				arr[1][j] = rand() % 5 + 1;
				arr[2][j] = rand() % 5 + 1;
				score += 50;
			}
			else if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] && arr[i][j + 2] == arr[i + 1][j + 2] && arr[i + 1][j + 2] == arr[i + 2][j + 2]) {
				arr[i][j + 2] += 10;
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 2][j] = arr[k + 1][j];
				}
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 1][j + 1] = arr[k][j + 1];
				}
				arr[0][j] = rand() % 5 + 1;
				arr[0][j + 1] = rand() % 5 + 1;

				arr[0][j] = rand() % 5 + 1;
				arr[1][j] = rand() % 5 + 1;
				score += 50;
			}
			else if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] && arr[i + 2][j] == arr[i + 2][j + 1] && arr[i + 2][j + 1] == arr[i + 2][j + 2]) {
				arr[i + 2][j] += 10;
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 2][j] = arr[k + 1][j];
				}
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j + 1] = arr[k][j + 1];
					arr[k + 1][j + 2] = arr[k][j + 2];
				}
				arr[0][j + 1] = rand() % 5 + 1;
				arr[0][j + 2] = rand() % 5 + 1;

				arr[0][j] = rand() % 5 + 1;
				arr[1][j] = rand() % 5 + 1;
				score += 50;
			}
			else if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] && arr[i][j + 2] == arr[i - 1][j + 2] && arr[i - 1][j + 2] == arr[i - 2][j + 2]) {
				arr[i][j + 2] += 10;
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 2][j] = arr[k + 1][j];
				}
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 1][j + 1] = arr[k][j + 1];
				}
				arr[0][j] = rand() % 5 + 1;
				arr[0][j + 1] = rand() % 5 + 1;

				arr[0][j] = rand() % 5 + 1;
				arr[1][j] = rand() % 5 + 1;
				score += 50;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DESTROYER BLAST HORIZONTAL

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			if (arr[i][j] - 10 == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2]) {
				destroyerBlast(arr, i, j, score);
			}
			else if (arr[i][j] == arr[i][j + 1] - 10 && arr[i][j + 1] - 10 == arr[i][j + 2]) {
				destroyerBlast(arr, i, j + 1, score);
			}
			else if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] - 10) {
				destroyerBlast(arr, i, j + 2, score);
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DESTROYER BLAST VERTICAL

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[i][j] - 10 == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j]) {
				destroyerBlast(arr, i, j, score);
			}
			else if (arr[i][j] == arr[i + 1][j] - 10 && arr[i + 1][j] - 10 == arr[i + 2][j]) {
				destroyerBlast(arr, i + 1, j, score);
			}
			else if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] - 10) {
				destroyerBlast(arr, i + 2, j, score);
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FOR 5 HORIZONTAL

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] && arr[i][j + 2] == arr[i][j + 3] && arr[i][j + 3] == arr[i][j + 4]) {
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 1][j + 1] = arr[k][j + 1];
					arr[k + 1][j + 3] = arr[k][j + 3];
					arr[k + 1][j + 4] = arr[k][j + 4];
				}
				arr[0][j] = rand() % 5 + 1;
				arr[0][j + 1] = rand() % 5 + 1;
				arr[i][j + 2] += 10;
				arr[0][j + 3] = rand() % 5 + 1;
				arr[0][j + 4] = rand() % 5 + 1;
				score += 50;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FOR 5 VERTICAL

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] && arr[i + 2][j] == arr[i + 3][j] && arr[i + 3][j] == arr[i + 4][j]) {
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 2][j] = arr[k + 1][j];
					arr[k + 3][j] = arr[k + 2][j];
					arr[k + 3][j] = arr[k + 2][j];
				}
				arr[0][j] = rand() % 5 + 1;
				arr[1][j] = rand() % 5 + 1;
				arr[2][j] = rand() % 5 + 1;
				arr[3][j] = rand() % 5 + 1;
				arr[i + 4][j] += 10;
				score += 50;
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FOR 4 HORIZONTAL

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 5; j++) {
			if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] && arr[i][j+2] == arr[i][j+3]) {
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 1][j + 1] = arr[k][j + 1];
					arr[k + 1][j + 2] = arr[k][j + 2];
				}
				arr[0][j] = rand() % 5 + 1;
				arr[0][j + 1] = rand() % 5 + 1;
				arr[0][j + 2] = rand() % 5 + 1;
				arr[i][j + 3] += 5;
				score += 40;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FOR 4 VERTICAL

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] && arr[i+2][j] == arr[i+3][j]) {
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 2][j] = arr[k + 1][j];
					arr[k + 3][j] = arr[k + 2][j];
				}
				arr[0][j] = rand() % 5 + 1;
				arr[1][j] = rand() % 5 + 1;
				arr[2][j] = rand() % 5 + 1;
				arr[i + 3][j] += 5;
				score += 40;
			}
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// POWER BLAST HORIZONTAL

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			if (arr[i][j]-5 == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2]) {
				powerBlast(arr, i, j, score);
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j + 2] = arr[k][j + 2];
				}
				arr[0][j + 2] = rand() % 5 + 1;
			} else if (arr[i][j] == arr[i][j + 1]-5 && arr[i][j + 1]-5 == arr[i][j + 2]) {
				powerBlast(arr, i, j+1, score);
			}
			else if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] - 5) {
				powerBlast(arr, i, j + 2, score);
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
				}
				arr[0][j] = rand() % 5 + 1;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// POWER BLAST VERTICAL

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[i][j] - 5 == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j]) {
				powerBlast(arr, i, j, score);
			}
			else if (arr[i][j] == arr[i + 1][j] - 5 && arr[i + 1][j] - 5 == arr[i + 2][j]) {
				powerBlast(arr, i+1, j, score);
			}
			else if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] - 5) {
				powerBlast(arr, i + 2, j, score);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FOR 3 HORIZONTAL

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			if ((arr[i][j] > 5 && (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] + 5)) || 
				(arr[i][j] > 5 && (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] + 5 == arr[i][j + 2] + 5))) {
				powerBlast(arr, i, j + 1, score);
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FOR 3 VERTICAL

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			if ((arr[i][j] > 5 && (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] + 5)) ||
				(arr[i][j] > 5 && (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] + 5 == arr[i][j + 2] + 5))) {
				powerBlast(arr, i + 1, j, score);

			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FOR 3 HORIZONTAL

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2]) {
				for (int k = i - 1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 1][j + 1] = arr[k][j + 1];
					arr[k + 1][j + 2] = arr[k][j + 2];
				}
				arr[0][j] = rand() % 5 + 1;
				arr[0][j + 1] = rand() % 5 + 1;
				arr[0][j + 2] = rand() % 5 + 1;
				score += 30;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FOR 3 VERTICAL

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j]) {
				for (int k = i-1; k >= 0; k--) {
					arr[k + 1][j] = arr[k][j];
					arr[k + 2][j] = arr[k+1][j];
					arr[k + 3][j] = arr[k+2][j];
				}
					arr[0][j] = rand() % 5 + 1;
					arr[1][j] = rand() % 5 + 1;
					arr[2][j] = rand() % 5 + 1;
					score += 30;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SCORE

	scoreDisplay.setString(to_string(score));
	game.draw(scoreDisplay);
	game.draw(select);

	game.display();
}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN WINDOW

int main() {

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// WINDOW

	RenderWindow window(VideoMode(1200, 800), "Bejeweled Blitz");

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// BACKGROUND

	Texture menuBgTexture;
	if(!menuBgTexture.loadFromFile("bg.jpg")) {}

	Sprite menuBg;
	menuBg.setScale(1200.f / menuBgTexture.getSize().x, 800.f / menuBgTexture.getSize().y);
	menuBg.setTexture(menuBgTexture);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TITLE

	Texture titleTexture;
	if (!titleTexture.loadFromFile("title.png")) {
		cout << "failed";
	}

	Sprite title;
	//title.setScale(500.f / titleTexture.getSize().x, 200.f / titleTexture.getSize().y);
	title.setTexture(titleTexture);
	title.setPosition(350, 100);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FONT

	Font font;
	if(!font.loadFromFile("RubikMonoOne-Regular.ttf")) {}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TEXT

	Text play;
	Text quit;

	play.setFont(font);
	quit.setFont(font);

	play.setString("PLAY");
	quit.setString("QUIT");

	play.setCharacterSize(70);
	quit.setCharacterSize(70);

	Color color(255, 50, 171);

	play.setFillColor(color);
	quit.setFillColor(color);

	play.setPosition(475, 375);
	quit.setPosition(475, 460);

	play.setOutlineThickness(3);
	play.setOutlineColor(Color::White);

	quit.setOutlineThickness(1);
	quit.setOutlineColor(Color::Black);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MAIN LOOP

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			// CURSOR HANDLER
			else if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					play.setOutlineColor(Color::Black);
					play.setOutlineThickness(1);
					quit.setOutlineThickness(3);
					quit.setOutlineColor(Color::White);
				} else if (Keyboard::isKeyPressed(Keyboard::Up)) {
					quit.setOutlineColor(Color::Black);
					quit.setOutlineThickness(1);
					play.setOutlineThickness(3);
					play.setOutlineColor(Color::White);
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				// QUIT FUNCTION
				if (quit.getOutlineColor() == Color::White) {
					if (event.type == Event::KeyPressed) {
						if (Keyboard::isKeyPressed(Keyboard::Return)) {
							window.close();
						}
					}
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				// PLAY FUNCTION
				else if (play.getOutlineColor() == Color::White) {
					if (event.type == Event::KeyPressed) {
						if (Keyboard::isKeyPressed(Keyboard::Return)) {
							window.close();
							playGame();
							
						}
					}
				}
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// MAIN WINDOW ELEMENTS DRAWER

		window.clear();
		window.draw(menuBg);
		window.draw(title);
		window.draw(play);
		window.draw(quit);

		window.display();
	}

	return 0;
}