Update 31.08.24
1. Naprawiłem problem z dublem przy export.
2. Stowrzyłem poprawne (chyba) formatowanie funkcja ft_check_format_export
3. Aby rozwiązać problem $ w różnych okolicznościach (ls, cd, echo, ?) możemy sprawdzić czy dany command->args[i].arg rozpoczyna się $.
Jeżeli tak to można podmienić np: $PWD na konkretną ścieżkę.
command->args[i].arg = $PWD na command->args[i].arg = /home/piotr
Rozpocząłem to umieszczając funkcję ft_dollar_check(head); w parsing.c 56 linijka. Jednak już wiem że może być problem z "". 

Update 02.09.24
1. Odpiąłem "echo" od funkcji is_builtin, echo wystarczy wrzucić do pipexa i ten już zrobi swoje. Zrobiłem to aby uprościć trochę sprawę z $.
W pliku parsing.c dodałem funkcję ft_dollar_check która podmienia 

- Ctrl-\ in Empty Prompt**: No action ✔ (czasem wyskakuje ^\ na moment, nie wiem czy sie z tym bawic)
- to samo z not emptry prompt**
  
- Set `$PATH` with Multiple Directories and Check Order: (chyba działa, lepiej żebyś sam ocenił) ✔
------------------

# Minishell Evaluation Checklist

## Compile
- **Compile with Flags**: Use `-Wall -Wextra -Werror` ✔
- **No Errors**: Ensure there are no compilation errors ✔
- **No Relinking**: Ensure there are no unnecessary relinks ✔

## Simple Command & Global Variables 
- **Execute `/bin/ls`**: ✔
- **No Global Variables**: Ensure no global variables are used ✔✔
- **Empty Command Line**: Handle empty command lines correctly ✔
- **Spaces or Tabs Only**: Handle lines with only spaces or tabs ✔✔

## Arguments
- **Execute`/bin/ls` with Arguments**: ✔
  przykład:	/bin/ls -l
  		/bin/ls -a

## Echo
- **Echo with and without Arguments**: ✔
- **Echo with `-n` Option**: ✔

## Exit
- **Exit with and without Arguments**: ✔
- **Exit with Various Arguments**: ✔

## Return Value of a Process
- **Execute sth with absolute path like `/bin/ls` and Check `echo $?`**: ✔
- **Check the printed value. You can do the same in bash in order to compare the results.** ✔
  **Try some wrong commands like '/bin/ls filethatdoesntexist'**
- **Try anything like expr $? + $?** ✔

## Signals
- **Ctrl-C in Empty Prompt**: Display a new line with a new prompt ✔
- **Ctrl-\ in Empty Prompt**: No action ✔ (czasem wyskakuje ^\ na moment, nie wiem czy sie z tym bawic)
- **Ctrl-D in Empty Prompt**: Quit minishell and relaunch ✔
- **Ctrl-C in Non-Empty Prompt**: Display a new line with a new prompt, buffer should be clean ✔
- **Ctrl-D in Non-Empty Prompt**: No action ✔
- **Ctrl-\ in Non-Empty Prompt**: No action ✔
- **Ctrl-C after Blocking Command**: Proper handling with a new prompt ✔
- **Ctrl-\ after Blocking Command**: ✔
- **Ctrl-D after Blocking Command**: Properly exits ✔

## Double Quotes
- **Simple Command with Arguments and Double Quotes**: ✔
- **Command like `echo "cat lol.c | cat > lol.c"`**: ✔
- **Anything except `$`**: nie działa jeszce $

## Single Quotes
- **Commands with Single Quotes as Arguments**: ✔
- **Empty Arguments**: ✔
- **Environment Variables, Whitespaces, Pipes, Redirection in Single Quotes**: ❌?? redirsy w quotes
- **`echo '$USER'` must print "$USER"**: ✔
- **Nothing Should be Interpreted**:

## Environment Variables
- **Check `env` Command**: ✔

## Export
- **Export Environment Variables, Create New Ones, Replace Old Ones**: ✔
- **Check Result with `env`**: ✔

## Unset
- **Export, Create New Ones, Replace Old Ones**: ✔
- **Use `unset` to Remove Some**: ✔
- **Check Result with `env`**: ✔

## CD
- **Change Working Directory and Check with `/bin/ls`**: ✔
- **Repeat with Working and Non-Working Directories**: ✔
- **Use `.` and `..` as Arguments**: ✔

## PWD
- **Use `pwd` Command**: ✔
- **Repeat in Different Directories**: ✔

## Relative Path
- **Execute Commands with Relative Paths**: ✔
- **Complex Relative Paths with `..`**: ✔

## Environment Path
- **Execute Commands without Path (`ls`, `wc`, `awk`, etc.)**: ✔
- **Unset `$PATH` and Ensure Commands Don't Work**:
- **Set `$PATH` with Multiple Directories and Check Order**: (chyba działa, lepiej żebyś sam ocenił) ✔

## Redirection
- **Execute Commands with `<` and `>`**: ✔
- **Repeat with Different Commands and Use `>>`**: ✔
- **Ensure Multiple Redirections Fail**: ✔
- **Test `<<` Redirection**: ✔

## Pipes
- **Commands with Pipes like `cat file | grep bla | more`**: ✔
- **Repeat with Different Commands**: ✔
- **Wrong Commands like `ls filethatdoesntexist | grep bla | more`**: ✔
- **Mix Pipes and Redirections**: (Not sure)

## Go Crazy and History
- **Ctrl-C and Enter Should Clean Buffer**: ✔
- **Navigate Through History with Up and Down**: ✔
- **Retry Commands from History**: ✔
- **Handle Wrong Commands Gracefully**: ✔
- **Command `cat | cat | ls` Should Work Normally**: ✔
- **Long Commands with Many Arguments**: (Not checked)

## Environment Variables Handling
- **Echo with Environment Variables (`$variable`)**: ✔ 
- **Check `$` as Environment Variable**: ✔
- **Double Quotes Should Interpolate `$`**: ✔ 
- **Check if `USER` Exists**: (Set if not)
- **`echo "$USER"` Should Print User Variable**: ✔ 

Update 29.07

- Zrobiłem prowizorkę w proces_input:
    	if(!cmd_list->args[0])
		return;
    Zabezpiecza przed brakiem parametru przed < i <<

Update 28.07

- Funkcja create_new_command nie korzysta z parametru który ma podany, na razie zrobiłem ten myk z (void)token; ale można po prostu zrobić parametr funckji jako void. 
- zrobiony export 
- poczyszczone trochę lekaów
- wróciły flagi wall wxtra werror

Update 27.07

- sygnały ctrl+D i ctrl+\ działa, chyba że jest jakiś case o którym nie pomyślałem
- przy ctrl+C jest problem jak sie zrobi przykładowo:
![image](https://github.com/user-attachments/assets/c920aa93-7c40-419e-b32e-21dfa41bb3da)

No ale to tka ma działać :) (image.png)



Update 24.07

- ft_strcmp albo ja czegoś nie kumam albo ta funkcja działą na odwrót. 
    Myślałem że zwróci true (1) jeżeli stringi będą takie same
    Anyway zrobiłem !ft_strcmp i mam pożądany efekt
- wrzucam listę na dole tego readme do malloców których nie zwolniłem.
    Będę uzupełniał na bieżąco. Jak się zrobi to się oznaczy o tak (done)
- nie zgadzają nam się czasmi komunikaty błędów. W bashu co innego u nas co innego.
    Nie wiem czy tak może być.


Update 23.07

do komendy env użyłem zmiennej globalnej, żeby pobierać zawartość env z kompa i tam poprostu trzymać, w sumie chyba można to zrobić podobnie jak w heredoc z zapisem do pliku to mogę to zmienić

------------------

1. git clone
2. git branch <nowy_branch>
3. git checkout <nowy_branch>
4. robota 
5. git add
6. git commit
7. git checkou <main/master>
8. git pull origin main/master
9. git merge <new_branch>
10. git push origin main/master 

------------------

https://42evals.com/
CVb3d2023

------------------

Update 11.07.24

Echo problematyczne gdy argument podany jest w "", jeszcze nie ogarnąłem tego

Update 07.07.24

Udało mi sie już jakoś połączyć procesy w pętlach. 
Póki co to działałem na harkodowanych zmiennych jak path, ilość komend itp
Na tą chwilę potrzeba:

1. Uzupełnić int num_of_cmds w s_gen - długość listy komend. Ja to mogę zrobić.		# w trakcie
2. Uzupełnić char *path w s_command - ścieżka do programu np: "/usr/bin/cat"		
3. Uzupełnić redirsy:
    a) int input_redir - będzie zawirać file descriptor będący wynikiem funckji open
    b) analogicznie output_redir;

Uzupełnienie tego powinno już pozwolić połączyć to wszystko.
Potem zajmiemy sie heredoc i append.

--------------------------------------------------------------------------

Robię tak że execute_pipeline przyjmie następujące informacje
1. input redirection w formie ścieżki pliku w postaci 
    stringa np: "infile.txt"
2. porzebuję ścieżki do każdej komendy znajdującej się command.
    Utworzyłem membere commant->path. Scieżka powinna wyglądać np:
    "/usr/bin/ls" dla programu ls 



To free
1. input będącym member t_history
2. Każdy node t_history
