#pragma once

#include <QLineEdit>
#include <QMainWindow>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui {
class SudokuSolver;
}
QT_END_NAMESPACE

class SudokuSolver : public QMainWindow {
  Q_OBJECT

public:
  SudokuSolver(QWidget *parent = nullptr);
  ~SudokuSolver();

private slots:
  void on_pushButton_Solve_clicked();
  void on_pushButton_Clear_clicked();
  void onLineEdit0(int id);
  void onLineEdit1(int id);
  void onLineEdit2(int id);
  void onLineEdit3(int id);
  void onLineEdit4(int id);
  void onLineEdit5(int id);
  void onLineEdit6(int id);
  void onLineEdit7(int id);
  void onLineEdit8(int id);

private:
  Ui::SudokuSolver *ui;
  QLineEdit **sudokuCell;
  const int boardSize = 9;
  void initializeCells();
  void clearCells();

  void solve();
  bool solveUtils(int row, int col);
  bool isValidPlacement(int row, int col, char value);
  void displayBoard();

  QSignalMapper *signalMapper0[9];
  QSignalMapper *signalMapper1[9];
  QSignalMapper *signalMapper2[9];
  QSignalMapper *signalMapper3[9];
  QSignalMapper *signalMapper4[9];
  QSignalMapper *signalMapper5[9];
  QSignalMapper *signalMapper6[9];
  QSignalMapper *signalMapper7[9];
  QSignalMapper *signalMapper8[9];
};
