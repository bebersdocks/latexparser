/* At least C++11 is required */
#include "LinkedStack.h"
#include <fstream>

string getEnv(string str) /* extract {environment} from the string */
{
  int start = str.find_first_of('{');
  int size = str.find_first_of('}') - (start - 1); /* in order to get precisely {env} -> we subtract one from { position */
  return str.substr(start, size);
}

string getLine(string str) /* extract line number (added to the end) from the string */
{
  int start = str.find_first_of("123456789", str.size() - 3); /* we need to look in the end, not to catch numbers in the middle */
  int size = str.size() - start;
  return str.substr(start, size);
}

/* return the stack elements ordered by the line number */
string concateStack(LinkedStack *stack)
{
  string str = stack->topEl();
  stack->pop(); /* rest of the list */
  if (stack->isEmpty())
    return getEnv(str) + " line " + getLine(str) + "\n";
  else
    return concateStack(stack) + /* reverse the order of the stack */
      getEnv(str) + " line " + getLine(str) + "\n";
}

string parseLatexFile(string filename)
{
  LinkedStack *stack = new LinkedStack();
  string line = "";
  int lineIndex = 1; /* start from 1, not 0 */
  ifstream file;
  file.open(filename);

  while (getline(file, line))
  {
    if (line.find("egin{") != string::npos) /* \begin is found -> add it to the stack */
      stack->push(line + " " + to_string(lineIndex)); /* we add line number to the end, we extract it when needed */
    else if (line.find("nd{") != string::npos) /* \end is found */
    {
      if (stack->isEmpty()) /* stack is empty (we don't have \begin's to match our \end) */
      {
        return "\nline " + to_string(lineIndex) + " : \\end " +
          getEnv(line) + " has no matching \\begin";
      }
      else if (getEnv(line) != getEnv(stack->topEl())) /* \end doesn't match to the nearest \begin */
      {
        return "\nline " + to_string(lineIndex) + " : \\end " +
          getEnv(line) + " does not match \\begin " +
          getEnv(stack->topEl()) + " on line " + getLine(stack->topEl());
      }
      else if (getEnv(line) == getEnv(stack->topEl())) /* \end matched to the nearest \begin */
        stack->pop(); /* remove matched \begin and procede to the next \end's */
    }
    lineIndex = lineIndex + 1;
  }

  if (!stack->isEmpty()) /* unmatched \begin's in the stack */
  	return "\nThe following enviroments have no matching \\end: \n" + concateStack(stack);

  file.close();
  delete stack;
  return "\nAll delimiters match"; /* if stack is empty and all \end's matched with \begin's */
}

int main()
{
  cout << parseLatexFile("text.tex");
}
