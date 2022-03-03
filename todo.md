# todo

## replace unautorized functions by our version :

in lexer/tokens.c :
	- l7 realloc
	- l9 bzero
	- l13 strndup
in parser/parser_handler.c :
	- l24 strdup
	- l60 strdup
	- l62 strdup
	- l64 strdup
	- l71 atoi
	- l74 atoi
in utils/cmd_utils.c :
	- l45 calloc
in utils/cmd_utils_2.c :
	- l11 calloc
	- l20 calloc
	- l23 memset
	- l25 strdup
in utils/str_insert.c :
	- l44 strlen
	- l45 strlen
in parser/handler_quote.c :
	- l61 strdup
in main.c :
	- l39 calloc
	- l90 strstr
