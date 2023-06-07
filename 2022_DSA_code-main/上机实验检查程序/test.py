from SampleGenerator import SampleGenerator1, SampleGenerator2, SampleGenerator4

def test_polyGenerator():
    [poly, deriv_poly_ans, integ_poly_ans, a, b, integ_value] = SampleGenerator1.calculusPolyGenerator()
    print(poly)
    print(deriv_poly_ans)
    print(integ_poly_ans)
    print(a, b)
    print(integ_value)
    
def test_exprGenerator():
    exprString = SampleGenerator2.wrongExpressionGenerator()
    print(exprString)

def test_graph():
    [namePath, length] = SampleGenerator4.graphAnswerGenerator("Xuzhou", "Guangzhou", deleteCityName="Wuhan")
    print(namePath)
    print(length)

if __name__ == "__main__":
    # test_polyGenerator()
    # test_exprGenerator()
    test_graph()
