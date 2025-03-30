from pytest_embedded_idf.dut import IdfDut

def test_adder(dut: IdfDut) -> None:
    dut.run_all_single_board_cases(group='adder')
    assert len(dut.testsuite.testcases) > 0, "No test cases found"
