#include "sudokusolver.h"
#include "QDebug"
#include "QIntValidator"
#include "QRegExpValidator"
#include "QtMath"
#include "ui_sudokusolver.h"
#include <iostream>
static char board[9][9] = {{0}};
SudokuSolver::SudokuSolver(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SudokuSolver) {
  ui->setupUi(this);
  for (int i = 0; i < boardSize; i++) {
    signalMapper0[i] = new QSignalMapper(this);
    signalMapper1[i] = new QSignalMapper(this);
    signalMapper2[i] = new QSignalMapper(this);
    signalMapper3[i] = new QSignalMapper(this);
    signalMapper4[i] = new QSignalMapper(this);
    signalMapper5[i] = new QSignalMapper(this);
    signalMapper6[i] = new QSignalMapper(this);
    signalMapper7[i] = new QSignalMapper(this);
    signalMapper8[i] = new QSignalMapper(this);
  }
  initializeCells();
  clearCells();
  for (int i = 0; i < boardSize; i++) {
    signalMapper0[i]->setMapping(&sudokuCell[0][i], i);
    connect(signalMapper0[i], SIGNAL(mapped(int)), this,
            SLOT(onLineEdit0(int)));
    connect(&sudokuCell[0][i], SIGNAL(editingFinished()), signalMapper0[i],
            SLOT(map()));

    signalMapper1[i]->setMapping(&sudokuCell[1][i], i);
    connect(signalMapper1[i], SIGNAL(mapped(int)), this,
            SLOT(onLineEdit1(int)));
    connect(&sudokuCell[1][i], SIGNAL(editingFinished()), signalMapper1[i],
            SLOT(map()));

    signalMapper2[i]->setMapping(&sudokuCell[2][i], i);
    connect(signalMapper2[i], SIGNAL(mapped(int)), this,
            SLOT(onLineEdit2(int)));
    connect(&sudokuCell[2][i], SIGNAL(editingFinished()), signalMapper2[i],
            SLOT(map()));

    signalMapper3[i]->setMapping(&sudokuCell[3][i], i);
    connect(signalMapper3[i], SIGNAL(mapped(int)), this,
            SLOT(onLineEdit3(int)));
    connect(&sudokuCell[3][i], SIGNAL(editingFinished()), signalMapper3[i],
            SLOT(map()));

    signalMapper4[i]->setMapping(&sudokuCell[4][i], i);
    connect(signalMapper4[i], SIGNAL(mapped(int)), this,
            SLOT(onLineEdit4(int)));
    connect(&sudokuCell[4][i], SIGNAL(editingFinished()), signalMapper4[i],
            SLOT(map()));

    signalMapper5[i]->setMapping(&sudokuCell[5][i], i);
    connect(signalMapper5[i], SIGNAL(mapped(int)), this,
            SLOT(onLineEdit5(int)));
    connect(&sudokuCell[5][i], SIGNAL(editingFinished()), signalMapper5[i],
            SLOT(map()));

    signalMapper6[i]->setMapping(&sudokuCell[6][i], i);
    connect(signalMapper6[i], SIGNAL(mapped(int)), this,
            SLOT(onLineEdit6(int)));
    connect(&sudokuCell[6][i], SIGNAL(editingFinished()), signalMapper6[i],
            SLOT(map()));

    signalMapper7[i]->setMapping(&sudokuCell[7][i], i);
    connect(signalMapper7[i], SIGNAL(mapped(int)), this,
            SLOT(onLineEdit7(int)));
    connect(&sudokuCell[7][i], SIGNAL(editingFinished()), signalMapper7[i],
            SLOT(map()));

    signalMapper8[i]->setMapping(&sudokuCell[8][i], i);
    connect(signalMapper8[i], SIGNAL(mapped(int)), this,
            SLOT(onLineEdit8(int)));
    connect(&sudokuCell[8][i], SIGNAL(editingFinished()), signalMapper8[i],
            SLOT(map()));
  }
}

SudokuSolver::~SudokuSolver() {
  if (sudokuCell) {
    for (int i = 0; i < boardSize; i++) {
      delete[] sudokuCell[i];
    }
    delete[] sudokuCell;
  }
  delete ui;
}

void SudokuSolver::on_pushButton_Solve_clicked() {
  solve();
  qDebug() << "Displaying";
  displayBoard();
}

void SudokuSolver::on_pushButton_Clear_clicked() { clearCells(); }

void SudokuSolver::onLineEdit0(int id) {
  board[0][id] = sudokuCell[0][id].text().data()->toLatin1();
}

void SudokuSolver::onLineEdit1(int id) {
  board[1][id] = sudokuCell[1][id].text().data()->toLatin1();
}

void SudokuSolver::onLineEdit2(int id) {
  board[2][id] = sudokuCell[2][id].text().data()->toLatin1();
}

void SudokuSolver::onLineEdit3(int id) {
  board[3][id] = sudokuCell[3][id].text().data()->toLatin1();
}

void SudokuSolver::onLineEdit4(int id) {
  board[4][id] = sudokuCell[4][id].text().data()->toLatin1();
}

void SudokuSolver::onLineEdit5(int id) {
  board[5][id] = sudokuCell[5][id].text().data()->toLatin1();
}

void SudokuSolver::onLineEdit6(int id) {
  board[6][id] = sudokuCell[6][id].text().data()->toLatin1();
}

void SudokuSolver::onLineEdit7(int id) {
  board[7][id] = sudokuCell[7][id].text().data()->toLatin1();
}

void SudokuSolver::onLineEdit8(int id) {
  board[8][id] = sudokuCell[8][id].text().data()->toLatin1();
}

void SudokuSolver::initializeCells() {
  sudokuCell = new QLineEdit *[boardSize];
  for (int i = 0; i < 9; i++) {
    sudokuCell[i] = new QLineEdit[boardSize];
  }
  sudokuCell[0][0].setParent(ui->frame);
  sudokuCell[0][0].resize(30, 30);
  sudokuCell[0][0].move(2, 2);
  int ax = 0;
  int ay = 2;
  for (int i = 0; i < boardSize; i++) {
    ax = 0;
    if (i % 3 == 0)
      ay += 2;
    for (int j = 0; j < boardSize; j++) {
      if (j % 3 == 0)
        ax += 2;
      sudokuCell[i][j].setParent(ui->frame);
      sudokuCell[i][j].resize(30, 30);
      sudokuCell[i][j].move(ax, ay);
      sudokuCell[i][j].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      sudokuCell[i][j].setInputMethodHints(Qt::ImhDigitsOnly);
      sudokuCell[i][j].setValidator(new QRegExpValidator(QRegExp("[1-9]")));
      ax += 36;
    }
    ay += 36;
  }
}

void SudokuSolver::clearCells() {
  if (sudokuCell) {
    for (int i = 0; i < boardSize; i++) {
      for (int j = 0; j < boardSize; j++) {
        sudokuCell[i][j].clear();
      }
    }
  }
}

void SudokuSolver::solve() { solveUtils(0, 0); }

bool SudokuSolver::solveUtils(int row, int col) {
  if (col == boardSize) {
    col = 0;
    row++;
  }

  if (row == boardSize) {
    return true;
  }

  if (board[row][col] != '\0') {
    return solveUtils(row, col + 1);
  } else {
    for (char value = '1'; value <= '9'; value++) {
      if (isValidPlacement(row, col, value)) {
        board[row][col] = value;
        if (solveUtils(row, col + 1))
          return true;
        board[row][col] = '\0';
      }
    }
  }
  return false;
}

bool SudokuSolver::isValidPlacement(int row, int col, char value) {
  int i = 0;
  // Check if value exist in current row
  for (i = 0; i < boardSize; i++) {
    if (board[row][i] == value) {
      return false;
    }
  }
  // Check if value exist in current col
  for (i = 0; i < boardSize; i++) {
    if (board[i][col] == value) {
      return false;
    }
  }
  // Check if value exist in current sub-section
  int regionSize = (int)qSqrt(boardSize);
  int rowIndex = row / regionSize;
  int colIndex = col / regionSize;
  int rowOffset = regionSize * rowIndex;
  int colOffset = regionSize * colIndex;
  for (i = 0; i < regionSize; i++) {
    for (int j = 0; j < regionSize; j++) {
      if (board[rowOffset + i][colOffset + j] == value) {
        return false;
      }
    }
  }
  return true;
}

void SudokuSolver::displayBoard() {
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      sudokuCell[i][j].setText(QString(board[i][j]));
    }
  }
}
