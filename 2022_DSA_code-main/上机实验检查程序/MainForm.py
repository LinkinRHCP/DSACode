import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5 import uic
from SampleGenerator import SampleGenerator1, SampleGenerator2, SampleGenerator4
import numpy as np

class MainForm(QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("MainForm.ui")
        self.ui.setWindowTitle("上机实验检查程序 ©2022 Minxuan Cai. All rights reserved.")
        self.ui.show()
        self.form_1_connect()
        self.form_2_connect()
        self.form_3_connect()
        self.form_4_connect()
        self.form_5_connect()
        
    def pushButton_clicked(self):
        [poly_A, poly_B, poly_ans] = SampleGenerator1.sumPolyGenerator()
        self.ui.lineEdit.setText(poly_A)
        self.ui.lineEdit_2.setText(poly_B)
        self.ui.lineEdit_3.setText(poly_ans)

    def pushButton_clicked_2(self):
        [poly_A, poly_B, poly_ans] = SampleGenerator1.minusPolyGenerator()
        self.ui.lineEdit_6.setText(poly_A)
        self.ui.lineEdit_5.setText(poly_B)
        self.ui.lineEdit_4.setText(poly_ans)

    def pushButton_clicked_3(self):
        [poly_A, poly_B, poly_ans] = SampleGenerator1.timesPolyGenerator()
        self.ui.lineEdit_9.setText(poly_A)
        self.ui.lineEdit_8.setText(poly_B)
        self.ui.lineEdit_7.setText(poly_ans)

    def pushButton_clicked_4(self):
        [poly_A, poly_B, rem_poly_ans, quo_poly_ans] = SampleGenerator1.dividePolyGenerator()
        self.ui.lineEdit_12.setText(poly_A)
        self.ui.lineEdit_11.setText(poly_B)
        self.ui.lineEdit_10.setText(rem_poly_ans)
        self.ui.lineEdit_13.setText(quo_poly_ans)

    def pushButton_clicked_5(self):
        [poly_A, poly_B, mc_poly_ans, lcm_poly_ans] = SampleGenerator1.mcAndLcmPolyGenerator()
        self.ui.lineEdit_16.setText(poly_A)
        self.ui.lineEdit_15.setText(poly_B)
        self.ui.lineEdit_14.setText(mc_poly_ans)
        self.ui.lineEdit_17.setText(lcm_poly_ans)

    def pushButton_clicked_6(self):
        [poly, deriv_poly_ans, integ_poly_ans, a, b, integ_value] = SampleGenerator1.calculusPolyGenerator()
        self.ui.lineEdit_20.setText(poly)
        self.ui.lineEdit_19.setText(integ_poly_ans)
        self.ui.lineEdit_18.setText(a)
        self.ui.lineEdit_22.setText(b)
        self.ui.lineEdit_21.setText(integ_value)

    def pushButton_clicked_7(self):
        for eachLineEdit in [self.ui.lineEdit, self.ui.lineEdit_2, self.ui.lineEdit_3, self.ui.lineEdit_4,
                            self.ui.lineEdit_5, self.ui.lineEdit_6, self.ui.lineEdit_7, self.ui.lineEdit_8,
                            self.ui.lineEdit_9, self.ui.lineEdit_10, self.ui.lineEdit_11, self.ui.lineEdit_12,
                            self.ui.lineEdit_13, self.ui.lineEdit_14, self.ui.lineEdit_15, self.ui.lineEdit_16,
                            self.ui.lineEdit_17, self.ui.lineEdit_18, self.ui.lineEdit_19, self.ui.lineEdit_20,
                            self.ui.lineEdit_21, self.ui.lineEdit_22]:
            eachLineEdit.setText("")

    def form_1_connect(self):
        # 多项式加法
        self.ui.pushButton.clicked.connect(self.pushButton_clicked)
        # 多项式减法
        self.ui.pushButton_2.clicked.connect(self.pushButton_clicked_2)
        # 多项式乘法
        self.ui.pushButton_3.clicked.connect(self.pushButton_clicked_3)
        # 商和余式
        self.ui.pushButton_4.clicked.connect(self.pushButton_clicked_4)
        # MC、LCM
        self.ui.pushButton_5.clicked.connect(self.pushButton_clicked_5)
        # 不定积分、定积分
        self.ui.pushButton_6.clicked.connect(self.pushButton_clicked_6)
        # 清空
        self.ui.pushButton_7.clicked.connect(self.pushButton_clicked_7)

    def pushButton_clicked_8(self):
        [exprString, exprValue] = SampleGenerator2.normalExpressionGenerator()
        self.ui.lineEdit_25.setText(exprString)
        self.ui.lineEdit_24.setText(exprValue)

    def pushButton_clicked_9(self):
        [exprString, exprValue] = SampleGenerator2.minusExpressionGenerator()
        self.ui.lineEdit_27.setText(exprString)
        self.ui.lineEdit_26.setText(exprValue)

    def pushButton_clicked_10(self):
        [exprString, exprValue] = SampleGenerator2.advancedExpressionGenerator(self.ui.checkBox.isChecked(), self.ui.checkBox_2.isChecked(), self.ui.checkBox_3.isChecked(), self.ui.checkBox_4.isChecked())
        self.ui.lineEdit_29.setText(exprString)
        self.ui.lineEdit_28.setText(exprValue)

    def pushButton_clicked_11(self):
        exprString = SampleGenerator2.wrongExpressionGenerator()
        self.ui.lineEdit_31.setText(exprString)

    def pushButton_clicked_12(self):
        for eachLineEdit in [self.ui.lineEdit_24, self.ui.lineEdit_25, self.ui.lineEdit_26, self.ui.lineEdit_27,
                            self.ui.lineEdit_28, self.ui.lineEdit_29, self.ui.lineEdit_31]:
            eachLineEdit.setText("")

    def form_2_connect(self):
        # 基本四则运算
        self.ui.pushButton_8.clicked.connect(self.pushButton_clicked_8)
        # 负数操作数
        self.ui.pushButton_9.clicked.connect(self.pushButton_clicked_9)
        # 更多运算
        self.ui.pushButton_10.clicked.connect(self.pushButton_clicked_10)
        # 语法错误提示
        self.ui.pushButton_11.clicked.connect(self.pushButton_clicked_11)
        # 清空
        self.ui.pushButton_12.clicked.connect(self.pushButton_clicked_12)
        # 队列
        self.ui.plainTextEdit_2.zoomIn(3)

    def form_3_connect(self):
        self.ui.plainTextEdit_3.zoomIn(3)

    def pushButton_clicked_13(self):
        startCityName = self.ui.comboBox.currentText()
        endCityName = self.ui.comboBox_2.currentText()
        deleteCityName = self.ui.comboBox_3.currentText() if self.ui.comboBox_3.currentIndex != 0 else None
        result = SampleGenerator4.graphAnswerGenerator(startCityName, endCityName, deleteCityName)
        if result:
            [stringPath, length] = result
            self.ui.plainTextEdit.setPlainText(stringPath)
            self.ui.lineEdit_23.setText(length)

    def pushButton_clicked_14(self):
        self.ui.plainTextEdit.setPlainText("")
        self.ui.lineEdit_23.setText("")

    def form_4_connect(self):
        # 插入items
        cityList = np.loadtxt("city.txt", dtype=str)[:,1]
        for index, eachCity in zip(range(len(cityList)), cityList):
            self.ui.comboBox.insertItem(index, eachCity)
            self.ui.comboBox_2.insertItem(index, eachCity)
            self.ui.comboBox_3.insertItem(index+1, eachCity)
        # 计算最短路径
        self.ui.pushButton_13.clicked.connect(self.pushButton_clicked_13)
        # 清空
        self.ui.pushButton_14.clicked.connect(self.pushButton_clicked_14)

    def form_5_connect(self):
        self.ui.plainTextEdit_4.zoomIn(3)

if __name__=="__main__":
    app = QApplication(sys.argv)
    window = MainForm()
    sys.exit(app.exec_())
