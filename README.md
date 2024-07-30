Evalsheet na 20-07

Compile
	- używamy -Wall -Wextra -Werror	 	✔
	- bez errorów 				✔
	- nie ma relinków			✔

Simple Command & global variables 
	- /bin/ls 				✔
![image](https://github.com/user-attachments/assets/08e42f86-75c7-483a-82e6-90c8ec1c0257)
	- nie używamy global variables		✔ ✔
	- pusty command line			✔
![image](https://github.com/user-attachments/assets/e9ab146f-d62d-436d-ab44-93f56c0fbd12)
	- only spaces or tabs			✔ ✔

Arguments
	- /bin/ls (nie do końca rozumiem) 	?

Echo
	- execute echo z argumentami i bez	✔
 	- execute echo z -n i bez		✔

Exit
	- execute exit z argumentami i bez	✔
 	- execute exit z różnymi argumentami	✔

Return value of a process
	- /bin/ls -> echo $?			❌ obsługa $ jeszczenie działa

Signals
	- ctrl-C in an empty prompt should display a new line with a new prompt.					✔
	- ctrl-\ in an empty prompt should not do anything.								✔
	- ctrl-D in an empty prompt should quit minishell --> RELAUNCH!							✔
	- ctrl-C in a prompt after you wrote some stuff should display a new line with a new prompt.			
	The buffer should be clean too. Press "Enter" to make sure nothing from the previous line is executed.		✔
	- ctrl-D in a prompt after you wrote some stuff should not do anything.						✔
	- ctrl-\ in a prompt after you wrote some stuff should not do anything.						✔
	- Try ctrl-C after running a command like cat without args or grep “something“.	✔❌ bo jest ten podwójny prompt
	- Try ctrl-\ after running a blocking command like cat without arguments or grep “something“.			❌
	- Try ctrl-D after running a blocking command like cat without arguments or grep “something“.			✔

 Double Quotes
 	- Execute a simple command with arguments and, this time, use also double quotes (you should try to include whitespaces too).													✔
	- Try a command like : echo "cat lol.c | cat > lol.c"								❌
	- Try anything except $.											?

 Single Quotes
	- Execute commands with single quotes as arguments.								✔
	- Try empty arguments.												❌
 ![image](https://github.com/user-attachments/assets/71209fe3-2800-4820-8b81-610856c29759)
	- Try environment variables, whitespaces, pipes, redirection in the single quotes.				❌
	- echo '$USER' must print "$USER".										❌
	- Nothing should be interpreted.


 env
 	- Check if env shows you the current environment variables.							✔

 export
 	- Export environment variables, create new ones and replace old ones.  						✔❌
  	jak tworzy nowe envy to nie robi nadpisania jak chcesz zmienić wartość tylko robi nowy o takiej samej nazwie
   ![image](https://github.com/user-attachments/assets/ddf8b45f-bae4-46b8-93de-1fb53bf269be)
	- Check the result with env.

 unset
	- Export environment variables, create new ones and replace old ones.						
	- Use unset to remove some of them.										
	- Check the result with env.											✔
 
 cd
	- Use the command cd to move the working directory and check if you are in the right directory with /bin/ls	✔
	- Repeat multiple times with working and not working cd								✔
	- Also, try '.' and '..' as arguments.										✔

 pwd
 	- Use the command pwd.												✔
	- Repeat multiple times in different directories.								✔

 Relative path
 	- Execute commands but this time use a relative path.								✔
	- Repeat multiple times in different directories with a complex relative path (lots of ..).			✔

 Enviroment path (nie sprawdzałem)
	- Execute commands but this time without any path (ls, wc, awk and so forth).
	- Unset the $PATH and ensure commands are not working anymore.
	- Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right.
 
 Redirection
	- Execute commands with redirections < and/or >									✔
	- Repeat multiple times with different commands and arguments and sometimes change > with >>			✔
	- Check if multiple tries of the same redirections fail.							✔
	- Test << redirection (it doesn't have to update the history).							✔

 Pipes
	- Execute commands with pipes like 'cat file | grep bla | more'					są jakieś ok ok ✔
	- Repeat multiple times with different commands and arguments.							✔
	- Try some wrong commands like 'ls filethatdoesntexist | grep bla | more'					✔
	- Try to mix pipes and redirections.									not sure

 Go crazy and history
 	- Type a command line, then use ctrl-C and press "Enter". The buffer should be clean and there should be nothing left to execute.													✔
	- Can we navigate through history using Up and Down? Can we retry some command?					✔
	- Execute commands that should not work like 'dsbksdgbksdghsd'. Ensure minishell doesn't crash and prints an error.
 															✔
	- 'cat | cat | ls' should behave in a "normal way".								✔
	- Try to execute a long command with a ton of arguments.					nie sprawdzałem

 Enviroment variables
	- Execute echo with some environment variables ($variable) as arguments.		nie działa jeszcze $	❌
	- Check that $ is interpreted as an environment variable.							❌
	- Check that double quotes interpolate $.									❌
	- Check that USER exists. Otherwise, set it.									
	- echo "$USER" should print the value of the USER variable.							❌


---------------------------------------------------------------------------------------------------------------------------
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
