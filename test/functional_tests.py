import os
import subprocess
import sys
import unittest

def absolute_path(relative_path):
  return os.path.join(os.path.abspath(sys.path[0]), relative_path) 

LOXPP_PATH = absolute_path('../bin/loxpp') 

def run_file(path):
  result = subprocess.run([LOXPP_PATH, path], stdout=subprocess.PIPE)
  return result.stdout.decode('utf-8').strip()

 
class LoxppOutputTest(unittest.TestCase):
 
    def setUp(self):
        pass
 
    def test_fibonacci(self):
      expected = 'Interpreter output:\n8'
      actual = run_file(absolute_path('fibonacci.lox'))
      self.assertEqual(expected, actual)

    def test_function_returns(self):
      expected = ("Interpreter output:\n"
        "20\n15\nadding strings!\n"
        "Returning nil explicitly\nnil\n"
        "Returning nil implicitly\nnil")
        
      actual = run_file(absolute_path('fn_returns.lox'))
      self.assertEqual(expected, actual)
        
    def test_while_loop(self):
      expected = 'Interpreter output:\n0\n1\n2\n3\n4'
      actual = run_file(absolute_path('simple_while_loop.lox'))
      self.assertEqual(expected, actual)
    
    def test_for_loop(self):
      expected = 'Interpreter output:\n0\n2\n4\n6\n8'
      actual = run_file(absolute_path('for_loop.lox'))
      self.assertEqual(expected, actual)
    
    def test_closure(self):
      expected = 'Interpreter output:\n1\n2'
      actual = run_file(absolute_path('closure.lox'))
      self.assertEqual(expected, actual)
    
    def test_this_bound_closure(self):
      expected = 'Interpreter output:\n<fn localFunction>\n<fn localFunction>'
      actual = run_file(absolute_path('this_closure.lox'))
      self.assertEqual(expected, actual)
 
    def test_recursive_countdown(self):
      expected = 'Interpreter output:\n3\n2\n1\n0'
      actual = run_file(absolute_path('recursive_countdown.lox'))
      self.assertEqual(expected, actual)
 
 
if __name__ == '__main__':
  unittest.main()
