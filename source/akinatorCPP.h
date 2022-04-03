
#define  TX_USE_SPEAK

#include "../include/TXLib.h"
#include "../include/akinator.h"
#include "../include/dump.h"
#include "../include/database.h"
#include "../Stack/stack.h"
#include "../include/tree.h"

void akinator(void)
{
    /*/tree_construct();

    Node* mum = add_node(5, nullptr);

    add_node(1, mum);
    add_node(9, mum);
    add_node(7, mum);
    add_node(10, mum);
    add_node(6, mum);
    add_node(8, mum);

    //add_node(0, mum);
    //add_node(4, mum);

    print_pre(mum);
    printf("\n");

    print_in(mum);
    printf("\n");

    print_post(mum);

    //tree_dump(mum);

    tree_destruct(mum);*/

    //=====

    Node* root = do_data_loading("data");

    voice_assistant("Hello! I'm MIPT assistant and I recognize the object. Are you ready...\n\n");

    interectiv(root);

    voice_assistant("I am formating your disk! See you soon!");

    //do_data_push(root, CONSOLE);

    do_data_push(root, "data", SECRET_MODE);

    //graph_tree_dump(root);

    tree_destruct(root);



    //*/

    //file_coder(secret_file);
    //file_decoder(secret_file);

    return ;
}

void interectiv(Node* root)
{
    static char answer[WORLD_LENGTH] = {};

    if (root->left_son || root->right_son)
    {

        //printf("Are they %s?\n", root->cell);

        questions_assistant("Are they", root->cell);

        while (1)
        {
            scanf("%s", answer);

            if (!strcmp(root->right_son->cell, "SECRET!"))
                if (secret_identificator(root, answer) == success)
                {
                    interectiv(root->right_son);
                    return;
                }
                else
                {
                    if (!strcmp(answer, "yes"))
                    {
                        interectiv(root->right_son->left_son);
                        return;
                    }
                    else if (!strcmp(answer, "no"))
                    {
                        interectiv(root->left_son);
                        return;
                    } //fix bugs
                    else
                    {
                        //printf("Please repeat. You can enter [yes] or [no].\n");

                        voice_assistant("Please repeat. You can enter [yes] or [no].\n");
                    }
                } else



            if (!strcmp(answer, "yes"))
            {
                interectiv(root->right_son);

                break;
            }
            else if (!strcmp(answer, "no"))
            {
                interectiv(root->left_son);

                break;
            }
            else if (secret_identificator(root, answer) == init)     //== init
            {
                interectiv(root->right_son);

                break;
            }
            else
            {
                //printf("Please repeat. You can enter [yes] or [no].\n");

                voice_assistant("Please repeat. You can enter [yes] or [no].\n");
            }
        }
    }
    else
    {
        //printf("Did you guess %s?\n", root->cell);    //root

        questions_assistant("Did you guess", root->cell);

        while (1)
        {
            scanf("%s", answer);

            if (!strcmp(answer, "yes"))
            {
                //printf("I'm never wrong!\n");

                putchar('\n');

                voice_assistant("I'm never wrong!\n");

                get_object_inform(root);

                voice_assistant("Do you want to repeat?\n");

                while (1)
                {
                    scanf("%s", answer);

                    if (!strcmp(answer, "yes"))
                    {
                        Node* mother = root;

                        while (mother->mother)
                            mother = mother->mother;

                        static size_t music_key = 0;

                        txPlaySound( music[music_key], SND_LOOP);

                        if (music_key == MUSIC_SIZE)
                            music_key = 0;
                        else
                            ++music_key;

                        interectiv(mother);

                        return;
                    }
                    else if (!strcmp(answer, "no"))
                        return;
                    else
                        voice_assistant("Please repeat. You can enter [yes] or [no].\n");
                }
            }
            else if (!strcmp(answer, "no"))
            {
                //printf("Oh, really? ");

                voice_assistant("Oh, really? Who did you think?\n");

                fix_mistake(root);

                //printf("Do you want to repeat?\n");

                voice_assistant("Do you want to repeat?\n");

                 while (1)
                 {
                    scanf("%s", answer);

                    if (!strcmp(answer, "yes"))
                    {
                        Node* mother = root;

                        while (mother->mother)
                            mother = mother->mother;

                        interectiv(mother);

                        return;
                    }
                    else if (!strcmp(answer, "no"))
                        return;
                    else
                        voice_assistant("Please repeat. You can enter [yes] or [no].\n");
                }
            }
            else
                voice_assistant("Please repeat. You can enter [yes] or [no].\n");
        }
    }
}

void fix_mistake(Node* wrong_node)
{
    if (!wrong_node)
        return;

    //static char answer[WORLD_LENGTH] = {};

    Node* right_node    = (Node*) calloc(1, sizeof (Node)),
        * old_node      = (Node*) calloc(1, sizeof (Node));

    *old_node = *wrong_node;

    assert (right_node && old_node);

    //printf("Who did you think?\n");

    //voice_assistant("Who did you think?\n");

    //scanf("%s", right_node->cell);

    scanf_string(stdin, &right_node->cell);

    //printf("What kind of difference he has?\n");

    voice_assistant("What kind of difference he has?\n");

    //scanf("%s", wrong_node->cell);

    scanf_string(stdin, &wrong_node->cell);

    wrong_node->left_son    = old_node;
    wrong_node->right_son   = right_node;

    old_node->mother        = wrong_node;
    right_node->mother      = wrong_node;

    right_node->left_son    = nullptr;
    right_node->right_son   = nullptr;
}

void get_object_inform(Node* node)
{
    if (!node)
        return;

    cStack stk(3);

    char* object_name = node->cell;

    while (node->mother)
    {
        if (!strcmp(node->mother->cell, "SECRET!")
            &&
            node == node->mother->left_son)
        {
            node = node->mother;

            continue;
        }

        stk.stack_push(node->mother->cell);

        if (node == node->mother->left_son)
            stk.stack_push("not");

        node = node->mother;

        //printf("%s", node->cell);
    }

    char* p_text = {};

    //printf("%d", stk.size);

    size_t size_val = stk.size - 1;

    //printf("Some information about %s: ", object_name);

    voice_assistant("Some information about", object_name);

    for (size_t ip = 0; ip < size_val; ip++)
    {
        stk.stack_pop(&p_text);

        //printf("%s ", p_text);

        if (strcmp(p_text, "not"))
            printf("%s, ", p_text);
        else
            printf("%s ", p_text);
    }

    stk.stack_pop(&p_text);

    printf("%s.\n\n", p_text);
} //*/


void scanf_string(FILE* in_file, char** string)
{
    char control_c = getc(in_file),
         input_c   = '\0';

    size_t real_size = 0;

    size_t capacity = WORLD_LENGTH;

    *string = (char*) calloc(capacity, sizeof (char));

    if (in_file == stdin)
    {
        if (control_c != '\n')                  //откуда появляется лишний n после второго считывания
            (*string)[real_size++] = control_c;

        while ( (input_c = getc(in_file)) != '\n')
        {
            (*string)[real_size++] = input_c;

             if (real_size == capacity - 1)    //size > cap
             {
                //printf("DUMP!!!\n");

                *string = (char*) realloc(*string, capacity * 2);

                capacity *= 2;
             }


        }

        //getc(in_file);
    }
    else
    {
        while ( (input_c = getc(in_file)) != '}' && input_c != '{' && input_c != '\n' && input_c != EOF)
        {
            (*string)[real_size++] = input_c;

             if (real_size == capacity - 1);
             {
                *string = (char*) realloc(*string, capacity * 2);

                capacity *= 2;
             }
        }

        ungetc(input_c, in_file);

        if (real_size)
            --real_size;
        else
            real_size;

        if ((*string)[real_size] != ' ' || control_c != ' ')
        {
            (*string)[real_size] = '\0';

            printf("\nSYNTAX ERROR HERE:%c%s\n", control_c, (*string));

            assert(SYNTAX_ERROR);
        }
    }

    (*string)[real_size] = '\0';

    return;
}

/*void voice_assistant(const char *const ex_phrase, const char *const add_phrase)
{
    LITE_MODE

    std::string phrase = ex_phrase;

    std::string command;

    if (add_phrase)
    {
        std::string phrase1 = add_phrase;

        command = "espeak -v +f3 \""+phrase+phrase1+"\"";
    }
    else
        command = "espeak -v +f3 \""+phrase+"\"";

    const char* Command = command.c_str();

    system (Command);
} //*/

void voice_assistant(const char *const ex_phrase, const char *const add_phrase)
{
    //txPlaySound("sound/assistant.wav", SND_NOSTOP);

    if (!add_phrase)
        printf(ex_phrase);

    std::string phrase = ex_phrase;

    std::string command;

    if (add_phrase)
    {
        std::string phrase1 = add_phrase;

        std::cout << phrase+" "+phrase1 << ":" << std::endl;

        command = speach_setting+phrase+" "+phrase1+voice_end;
    }
    else
        command = speach_setting+phrase+voice_end;

    const char* Command = command.c_str();

    LITE_MODE

    txSpeak(Command);
}

void questions_assistant(const char *const ex_phrase, const char *const add_phrase)
{
    //txPlaySound("sound/assistant.wav", SND_NOSTOP);

    std::string phrase = ex_phrase;

    std::string command;

    std::string phrase1 = add_phrase;

    std::cout << phrase+" "+phrase1+"?" << std::endl;

    command = speach_setting+phrase+" "+phrase1+"?"+voice_end;

    const char* Command = command.c_str();

    LITE_MODE

    txSpeak (Command);
}


