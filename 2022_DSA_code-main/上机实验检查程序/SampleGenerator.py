import random
import numpy as np
import copy

class SampleGenerator1:
    """
        第一次实验
    """
    @staticmethod
    def setPoly(order_i, coeff_i):
        """
            随机设置多项式
            系数排布：从0阶项到最高阶项
        """
        for order in range(order_i):
            each_coeff = int(random.random() * 41) - 20
            coeff_i.append(each_coeff)

    @staticmethod
    def stringlizePoly(order_i, coeff_i):
        """
            多项式转字符串，便于打印
        """
        poly_i = ""
        for order in range(order_i):
            each_coeff = coeff_i[order]
            if each_coeff == 0:
                continue
            sign = "+" if each_coeff >= 0 else "-"
            poly_i = f"{sign} {abs(round(each_coeff, 3))}x^{order} " + poly_i
        return poly_i

    @staticmethod
    def initPoly():
        """
            多项式初始化
            多项式的阶为0——2，阶数为1——3
            每一项的系数介于-20——20之间
        """
        coeff_i = []
        order_i = int(random.random() * 3) + 1
        poly_i = ""
        SampleGenerator1.setPoly(order_i, coeff_i)
        poly_i = SampleGenerator1.stringlizePoly(order_i, coeff_i)
        return [poly_i, order_i, coeff_i]

    @staticmethod
    def sumPolyGenerator():
        """
            检查两个多项式之和
        """
        # 设置多项式
        [poly_A, order_A, coeff_A] = SampleGenerator1.initPoly()
        [poly_B, order_B, coeff_B] = SampleGenerator1.initPoly()
        # 计算多项式之和
        order_ans = max(order_A, order_B)
        coeff_ans = np.zeros(order_ans)
        coeff_ans[:order_A] = coeff_A
        coeff_ans[:order_B] += coeff_B
        # 获取结果多项式
        poly_ans = SampleGenerator1.stringlizePoly(order_ans, coeff_ans)
        return [poly_A, poly_B, poly_ans]

    @staticmethod
    def minusPolyGenerator():
        """
            检查两个多项式之差
        """
        # 设置多项式
        [poly_A, order_A, coeff_A] = SampleGenerator1.initPoly()
        [poly_B, order_B, coeff_B] = SampleGenerator1.initPoly()
        # 计算多项式之差
        order_ans = max(order_A, order_B)
        coeff_ans = np.zeros(order_ans)
        coeff_ans[:order_A] = coeff_A
        coeff_ans[:order_B] -= coeff_B
        # 获取结果多项式
        poly_ans = SampleGenerator1.stringlizePoly(order_ans, coeff_ans)
        return [poly_A, poly_B, poly_ans]

    @staticmethod
    def timesPolyGenerator():
        """
            检查两个多项式之积
        """
        # 设置多项式
        [poly_A, order_A, coeff_A] = SampleGenerator1.initPoly()
        [poly_B, order_B, coeff_B] = SampleGenerator1.initPoly()
        # 计算多项式之积
        coeff_A.reverse()
        coeff_B.reverse()
        coeff_ans = list(np.convolve(coeff_A, coeff_B))
        coeff_ans.reverse()
        order_ans = len(coeff_ans)
        coeff_A.reverse()
        coeff_B.reverse()
        # 获取结果多项式
        poly_ans = SampleGenerator1.stringlizePoly(order_ans, coeff_ans)
        return [poly_A, poly_B, poly_ans]

    @staticmethod
    def dividePolyGenerator():
        """
            检查两个多项式之商和余数
        """
        # 设置多项式
        [poly_A, order_A, coeff_A] = SampleGenerator1.initPoly()
        [poly_B, order_B, coeff_B] = SampleGenerator1.initPoly()
        while (order_A < order_B) or ((order_A == order_B) and (abs(coeff_A[-1]) <= abs(coeff_B[-1]))):
            [poly_A, order_A, coeff_A] = SampleGenerator1.initPoly()
            [poly_B, order_B, coeff_B] = SampleGenerator1.initPoly()
        # 计算多项式之商和余数
        coeff_A.reverse()
        coeff_B.reverse()
        pA = np.poly1d(coeff_A)
        pB = np.poly1d(coeff_B)
        pans = pA / pB
        rem_coeff_ans = list(pans[0].coef)
        quo_coeff_ans = list(pans[1].coef)
        rem_coeff_ans.reverse()
        quo_coeff_ans.reverse()
        rem_order_ans = len(rem_coeff_ans)
        quo_order_ans = len(quo_coeff_ans)
        coeff_A.reverse()
        coeff_B.reverse()
        # 获取结果多项式
        rem_poly_ans = SampleGenerator1.stringlizePoly(rem_order_ans, rem_coeff_ans)
        quo_poly_ans = SampleGenerator1.stringlizePoly(quo_order_ans, quo_coeff_ans)
        return [poly_A, poly_B, rem_poly_ans, quo_poly_ans]

    @staticmethod
    def mcAndLcmPolyGenerator():
        """
            检查两个多项式的最大公约式和最小公倍式
            目前只生成最简单的例子
        """
        # 设置多项式
        [poly_A, order_A, coeff_A] = SampleGenerator1.initPoly()
        [poly_B, order_B, coeff_B] = SampleGenerator1.initPoly()
        while order_A <= order_B:
            [poly_A, order_A, coeff_A] = SampleGenerator1.initPoly()
            [poly_B, order_B, coeff_B] = SampleGenerator1.initPoly()
        # 最简单的例子
        order_A = 3
        order_B = 2
        coeff_A = [-1, 0, 1]
        coeff_B = [-1, 1]
        poly_A = SampleGenerator1.stringlizePoly(order_A, coeff_A)
        poly_B = SampleGenerator1.stringlizePoly(order_B, coeff_B)
        # 计算多项式的最大公约式
        coeff_A.reverse()
        coeff_B.reverse()
        # 辗转相除，直到商为0
        pA = np.poly1d(coeff_A)
        pB = np.poly1d(coeff_B)
        pans = pA / pB
        while not (len(pans[1].coef) == 1 and pans[1].coef[0] == 0):
            pA = pB
            pB = pans[1]
            pans = pA / pB
        # 此时除式即为最大公约式
        mc_coeff_ans = list(pB.coef)
        # 最大公约式p乘以"两多项式除以p的商"，得到最小公倍式
        pA = np.poly1d(coeff_A)
        pB = np.poly1d(coeff_B)
        pmc = np.poly1d(mc_coeff_ans)
        plcm = (pA / pmc)[0] * (pB / pmc)[0] * pmc
        lcm_coeff_ans = list(plcm.coef)
        # 还原系数列表
        coeff_A.reverse()
        coeff_B.reverse()
        mc_coeff_ans.reverse()
        mc_order_ans = len(mc_coeff_ans)
        lcm_coeff_ans.reverse()
        lcm_order_ans = len(lcm_coeff_ans)
        # 获取结果多项式
        mc_poly_ans = SampleGenerator1.stringlizePoly(mc_order_ans, mc_coeff_ans)
        lcm_poly_ans = SampleGenerator1.stringlizePoly(lcm_order_ans, lcm_coeff_ans)
        return [poly_A, poly_B, mc_poly_ans, lcm_poly_ans]

    @staticmethod
    def calculusPolyGenerator():
        """
            检查多项式的微分与积分
        """
        # 设置多项式
        [poly, order, coeff] = SampleGenerator1.initPoly()
        # 构建多项式对象
        coeff.reverse()
        p = np.poly1d(coeff)
        # 微分
        p_deriv = np.poly1d.deriv(p)
        # 不定积分
        p_integ = np.poly1d.integ(p)
        # 定积分
        a = int(random.random() * 31) - 20
        b = a + int(random.random() * 10) + 1
        integ_value = p_integ(b) - p_integ(a)
        # 还原系数
        coeff.reverse()
        deriv_coeff_ans = list(p_deriv.coef)
        deriv_coeff_ans.reverse()
        deriv_order_ans = len(deriv_coeff_ans)
        integ_coeff_ans = list(p_integ.coef)
        integ_coeff_ans.reverse()
        integ_order_ans = len(integ_coeff_ans)
        # 获取结果多项式
        deriv_poly_ans = SampleGenerator1.stringlizePoly(deriv_order_ans, deriv_coeff_ans)
        integ_poly_ans = SampleGenerator1.stringlizePoly(integ_order_ans, integ_coeff_ans)
        return [poly, deriv_poly_ans, integ_poly_ans + " + C", str(a), str(b), str(integ_value)]

class SampleGenerator2:
    """
        第二次实验
    """
    # 计数器
    COUNTER = 0
    # 文法产生式定义
    # 普通四则运算
    NORMAL_EXPRESSION = {"NE":[["E", "OP", "E"]],
                        "E":[["(", "E", ")"], ["E", "OP", "E"], ["NUM"]],
                        "OP":[["+"], ["-"], ["*"], ["/"]]}
    # 高级运算-备份
    ADVANCED_EXPRESSION_TEMPLATE = {"AE":[["E", "OP", "E"]],
                        "E":[["(", "E", ")"], ["E", "OP", "E"], ["NUM"], ["F", "(", "E", ")"]],
                        "F":[],
                        "OP":[["+"], ["-"], ["*"], ["/"]]}
    
    # 高级运算
    ADVANCED_EXPRESSION = None

    # 带负数的运算
    MINUS_EXPRESSION = {"ME":[["E", "OP", "E"]],
                        "E":[["(", "E", ")"], ["E", "OP", "E"], ["NUM"]],
                        "OP":[["+"], ["-"], ["*"], ["/"]]}

    # 错误语法的生成
    WRONG_EXPRESSION = {"WE":[["E", "OP", "E"]],
                        "E":[["(", "E"], ["E", "OP"], ["NUM"]],
                        "OP":[["++"], [","]]}

    @staticmethod
    def randomByWeight(weight_list):
        weight_sum = sum(weight_list)
        x = int(random.random() * weight_sum) + 1
        temp = 0
        for idx, weight in zip(range(len(weight_list)), weight_list):
            temp += weight
            if x <= temp:
                SampleGenerator2.COUNTER += 1
                return idx
        return idx

    @staticmethod
    def generateNormalExprList(inputLex):
        """
            递归方式，随机生成普通四则运算表达式
        """
        outputExprList = []
        # 非终结符情形
        if inputLex == "NE":
            for eachLex in SampleGenerator2.NORMAL_EXPRESSION[inputLex][0]:
                outputExprList += SampleGenerator2.generateNormalExprList(eachLex)
        elif inputLex == "E":
            weight_0 = 1.8**SampleGenerator2.COUNTER
            weight_1 = 2**SampleGenerator2.COUNTER
            weight_2 = -1 + 1.5**(2 * SampleGenerator2.COUNTER)
            choose_idx = SampleGenerator2.randomByWeight([weight_0, weight_1, weight_2])
            for eachLex in SampleGenerator2.NORMAL_EXPRESSION[inputLex][choose_idx]:
                outputExprList += SampleGenerator2.generateNormalExprList(eachLex)
        elif inputLex == "OP":
            choose_idx = int(random.random() * 4)
            for eachLex in SampleGenerator2.NORMAL_EXPRESSION[inputLex][choose_idx]:
                outputExprList += SampleGenerator2.generateNormalExprList(eachLex)
        # 终结符情形
        else:
            # NUMBER需要替换为数字
            if inputLex == "NUM":
                outputExprList += str(int(random.random() * 20) + 1)
            else:
                outputExprList += inputLex
        return outputExprList

    @staticmethod
    def normalExpressionGenerator():
        SampleGenerator2.COUNTER = 0
        inputLex = "NE"
        exprList = SampleGenerator2.generateNormalExprList(inputLex)
        exprString = ""
        for eachExpr in exprList:
            exprString += eachExpr
        exprValue = round(eval(exprString), 3)
        return [exprString, str(exprValue)]

    @staticmethod
    def generateAdvancedExprList(inputLex):
        """
            递归方式，随机生成高级四则运算表达式
        """
        outputExprList = []
        # 非终结符情形
        if inputLex == "AE":
            for eachLex in SampleGenerator2.ADVANCED_EXPRESSION[inputLex][0]:
                outputExprList += SampleGenerator2.generateAdvancedExprList(eachLex)
        elif inputLex == "E":
            # weight_0 = 1.8**SampleGenerator2.COUNTER
            # weight_1 = 2**SampleGenerator2.COUNTER
            # weight_2 = -1 + 1.5**(2 * SampleGenerator2.COUNTER)
            # weight_3 = 1.5 + 1.5**(2 * SampleGenerator2.COUNTER)
            # choose_idx = SampleGenerator2.randomByWeight([weight_0, weight_1, weight_2, weight_3])
            choose_idx = int(random.random() * len(SampleGenerator2.ADVANCED_EXPRESSION[inputLex]))
            for eachLex in SampleGenerator2.ADVANCED_EXPRESSION[inputLex][choose_idx]:
                outputExprList += SampleGenerator2.generateAdvancedExprList(eachLex)
        elif inputLex == "F":
            choose_idx = int(random.random() * len(SampleGenerator2.ADVANCED_EXPRESSION[inputLex]))
            for eachLex in SampleGenerator2.ADVANCED_EXPRESSION[inputLex][choose_idx]:
                outputExprList += SampleGenerator2.generateAdvancedExprList(eachLex)
        elif inputLex == "OP":
            choose_idx = int(random.random() * len(SampleGenerator2.ADVANCED_EXPRESSION[inputLex]))
            for eachLex in SampleGenerator2.ADVANCED_EXPRESSION[inputLex][choose_idx]:
                outputExprList += SampleGenerator2.generateAdvancedExprList(eachLex)
        # 终结符情形
        else:
            # NUMBER需要替换为数字
            if inputLex == "NUM":
                outputExprList += str(int(random.random() * 5) + 1)
            else:
                outputExprList += inputLex
        return outputExprList

    @staticmethod
    def advancedExpressionGenerator(triangleFlag, lnFlag, sqrtFlag, powerFlag):
        SampleGenerator2.ADVANCED_EXPRESSION = copy.deepcopy(SampleGenerator2.ADVANCED_EXPRESSION_TEMPLATE)
        if not (triangleFlag or lnFlag or sqrtFlag or powerFlag):
            return ["全都没有，怎么生成", str("(╯°Д°)╯︵ ┻━┻")]
        if triangleFlag:
            SampleGenerator2.ADVANCED_EXPRESSION["F"].append(["sin"])
            SampleGenerator2.ADVANCED_EXPRESSION["F"].append(["cos"])
        if lnFlag:
            SampleGenerator2.ADVANCED_EXPRESSION["F"].append(["ln"])
        if sqrtFlag:
            SampleGenerator2.ADVANCED_EXPRESSION["F"].append(["sqrt"])
        if powerFlag:
            SampleGenerator2.ADVANCED_EXPRESSION["E"].append(["NUM", "^", "NUM"])
            if not (triangleFlag or lnFlag or sqrtFlag):
                SampleGenerator2.ADVANCED_EXPRESSION["E"][SampleGenerator2.ADVANCED_EXPRESSION["E"].index(["F", "(", "E", ")"])] = ["NUM"]
        SampleGenerator2.COUNTER = 0
        inputLex = "AE"
        try:
            exprList = SampleGenerator2.generateAdvancedExprList(inputLex)
        except:
            return ["再试一遍", "再试一遍"]
        exprString = ""
        exprStringPython = ""
        for eachExpr in exprList:
            exprString += eachExpr
            exprStringPython += eachExpr
        exprStringPython = exprStringPython.replace("sin", "np.sin")
        exprStringPython = exprStringPython.replace("cos", "np.cos")
        exprStringPython = exprStringPython.replace("ln", "np.log")
        exprStringPython = exprStringPython.replace("sqrt", "np.sqrt")
        exprStringPython = exprStringPython.replace("^", "**")
        try:
            exprValue = round(eval(exprStringPython), 3)
        except:
            exprValue = "再试一遍"
        return [exprString, str(exprValue)]

    @staticmethod
    def generateMinusExprList(inputLex):
        """
            递归方式，随机生成带负数的四则运算表达式
        """
        outputExprList = []
        # 非终结符情形
        if inputLex == "ME":
            for eachLex in SampleGenerator2.MINUS_EXPRESSION[inputLex][0]:
                outputExprList += SampleGenerator2.generateMinusExprList(eachLex)
        elif inputLex == "E":
            weight_0 = 1.8**SampleGenerator2.COUNTER
            weight_1 = 2**SampleGenerator2.COUNTER
            weight_2 = -1 + 1.5**(2 * SampleGenerator2.COUNTER)
            choose_idx = SampleGenerator2.randomByWeight([weight_0, weight_1, weight_2])
            for eachLex in SampleGenerator2.MINUS_EXPRESSION[inputLex][choose_idx]:
                outputExprList += SampleGenerator2.generateMinusExprList(eachLex)
        elif inputLex == "OP":
            choose_idx = int(random.random() * 4)
            for eachLex in SampleGenerator2.MINUS_EXPRESSION[inputLex][choose_idx]:
                outputExprList += SampleGenerator2.generateMinusExprList(eachLex)
        # 终结符情形
        else:
            # NUMBER需要替换为数字
            if inputLex == "NUM":
                sign = "" if random.random() >= 0.5 else "-"
                outputExprList += sign + str(int(random.random() * 20) + 1)
            else:
                outputExprList += inputLex
        return outputExprList

    @staticmethod
    def minusExpressionGenerator():
        SampleGenerator2.COUNTER = 0
        inputLex = "ME"
        exprList = SampleGenerator2.generateMinusExprList(inputLex)
        exprString = ""
        for eachExpr in exprList:
            exprString += eachExpr
        exprValue = round(eval(exprString), 3)
        return [exprString, str(exprValue)]

    @staticmethod
    def generateWrongExprList(inputLex):
        """
            递归方式，随机生成错误四则运算表达式
        """
        outputExprList = []
        # 非终结符情形
        if inputLex == "WE":
            for eachLex in SampleGenerator2.WRONG_EXPRESSION[inputLex][0]:
                outputExprList += SampleGenerator2.generateWrongExprList(eachLex)
        elif inputLex == "E":
            weight_0 = 1.8**SampleGenerator2.COUNTER
            weight_1 = 2**SampleGenerator2.COUNTER
            weight_2 = -1 + 1.5**(2 * SampleGenerator2.COUNTER)
            choose_idx = SampleGenerator2.randomByWeight([weight_0, weight_1, weight_2])
            for eachLex in SampleGenerator2.WRONG_EXPRESSION[inputLex][choose_idx]:
                outputExprList += SampleGenerator2.generateWrongExprList(eachLex)
        elif inputLex == "OP":
            choose_idx = int(random.random() * 2)
            for eachLex in SampleGenerator2.WRONG_EXPRESSION[inputLex][choose_idx]:
                outputExprList += SampleGenerator2.generateWrongExprList(eachLex)
        # 终结符情形
        else:
            # NUMBER需要替换为数字
            if inputLex == "NUM":
                outputExprList += str(int(random.random() * 20) + 1)
            else:
                outputExprList += inputLex
        return outputExprList

    @staticmethod
    def wrongExpressionGenerator():
        SampleGenerator2.COUNTER = 0
        inputLex = "WE"
        exprList = SampleGenerator2.generateWrongExprList(inputLex)
        exprString = ""
        for eachExpr in exprList:
            exprString += eachExpr
        return exprString

class MGraph:
    def __init__(self, vexList):
        self.vexList = list(vexList)
        self.vexNum = len(vexList)
        self.arcs = np.ones((self.vexNum, self.vexNum)) * np.inf

    def addArc(self, startVex, endVex, weight):
        self.arcs[startVex][endVex] = weight
        self.arcs[endVex][startVex] = weight

    def deleteVex(self, data):
        delete_idx = self.locateVex(data)
        if delete_idx == -1:
            return
        for i in range(self.vexNum):
            self.arcs[i][delete_idx] = np.inf
            self.arcs[delete_idx][i] = np.inf

    def locateVex(self, data):
        if data in self.vexList:
            return self.vexList.index(data)
        else:
            return -1

class SampleGenerator4:
    """
        第四次实验
    """
    NODE_LIMIT = 30
    @staticmethod
    def graphAnswerGenerator(startCityName, endCityName, deleteCityName=None):
        vexList = np.loadtxt("city.txt", dtype="str")[:,1]
        graph = MGraph(vexList)
        arcList = np.loadtxt("dist.txt", dtype=int)
        for eachArc in arcList:
            graph.addArc(eachArc[0], eachArc[1], eachArc[2])
        if deleteCityName:
            graph.deleteVex(deleteCityName)
        # dij算法
        if graph.locateVex(startCityName) == -1 or graph.locateVex(endCityName) == -1:
            return
        D = np.zeros(SampleGenerator4.NODE_LIMIT)
        P = np.ones((SampleGenerator4.NODE_LIMIT, SampleGenerator4.NODE_LIMIT), dtype=int) * -1
        SampleGenerator4.Dijkstra(graph, graph.locateVex(startCityName), D, P)
        path = list(P[graph.locateVex(endCityName)])
        path = path[:path.index(-1)]
        namePath = []
        stringPath = ""
        for eachPathIdx in path:
            namePath.append(graph.vexList[eachPathIdx])
            stringPath += graph.vexList[eachPathIdx] + " -> "
        stringPath = stringPath[:-4]
        length = 0
        for i in range(1, len(path)):
            length += graph.arcs[path[i-1]][path[i]]
        return [stringPath, str(int(length))]

    @staticmethod
    def Dijkstra(G, v0, D, P):
        k = -1
        S = np.zeros(SampleGenerator4.NODE_LIMIT, dtype=int)
        for i in range(G.vexNum):
            D[i] = G.arcs[v0][i]
            if not np.isinf(D[i]):
                P[i][0] = v0; P[i][1] = i; P[i][2] = -1
        S[v0] = 1
        D[v0] = 0
        for i in range(G.vexNum):
            min = np.inf
            for j in range(G.vexNum):
                if (not S[j]) and (D[j] < min):
                    min = D[j]
                    k = j
            if k == -1:
                return
            S[k] = 1
            for j in range(G.vexNum):
                if (not S[j]) and (D[k] + G.arcs[k][j] < D[j]):
                    D[j] = D[k] + G.arcs[k][j]
                    w = 0
                    while P[k][w] != -1:
                        P[j][w] = P[k][w]
                        w += 1
                    P[j][w] = j
                    P[j][w+1] = -1
