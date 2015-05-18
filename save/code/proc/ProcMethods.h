# define currentPlace memory_.at(index)

bool Proc :: loadMem (const char* filename)
{
    FILE* file = fopen (filename, "r");
    if ( !file )
    {
        printf ("Cant find:%s file\n", filename);
        return false;
    }
    int size = 0;
    char name[MAX_DATA]={};
    fscanf (file, "%s", name);
    if ( strcmp (name, HEADER) )
    {
        printf ("Bad file - bad haeder\n");
        return false;
    }
    fscanf (file, "%d", &startPoint_);
    fscanf (file, "%d", &size);
    for (int i = 0; i < size; i++)
    {
        ExecByte mem = {};
        int tempData = 0;
        fscanf (file, "%d %d %d %d %d", &mem.head[0], &mem.head[1], &mem.head[2], &mem.head[3], &tempData);
        mem.data = tempData;
        memory_.push_back (mem);
    }

    return true;
}

bool Proc :: execute ()
{
    unsigned int index = startPoint_;
    while (true)
    {
        if ( index >= memory_.size() )
        {
            printf ("Executing failure - out of bound\n");
            return false;
        }

        if ( currentPlace.head[0] == COMMAND::STOP_PROC )
        {
            printf ("Proc reached stop\n");
            break;
        }
        else if ( currentPlace.head[0] == COMMAND::PUSH )
        {
            if ( currentPlace.head[1] == PLACE::REGISTER )
            {
                stack_.push (reg_[currentPlace.head[2]]);
            }
            else if ( currentPlace.head[1] == PLACE::MEMORY )
            {
                stack_.push (currentPlace.data);
            }
        }
        else if ( currentPlace.head[0] == COMMAND::POP )
        {
            if ( stack_.size () == 0 )
            {
                printf ("Trying to pop from empty stack\n");
                return false;
            }
            if ( currentPlace.head[1] == PLACE::NOWHERE )
            {
                stack_.pop ();
            }
            else if ( currentPlace.head[1] == PLACE::REGISTER )
            {
                reg_[currentPlace.head[2]] = stack_.top ();
                stack_.pop ();
            }
        }
        else if ( currentPlace.head[0] == COMMAND::TOP )
        {
            if ( stack_.size () == 0 )
            {
                printf ("Trying to top from empty stack\n");
                return false;
            }
            reg_[currentPlace.head[2]] = stack_.top ();
            stack_.pop ();
        }
        else if ( currentPlace.head[0] == COMMAND::ADD )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to math in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            num1 = num2 + num1;
            stack_.push (num1);
        }
        else if ( currentPlace.head[0] == COMMAND::SUB )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to math in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            num1 = num2 - num1;
            stack_.push (num1);
        }
        else if ( currentPlace.head[0] == COMMAND::MUL )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to math in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            num1 = num2 * num1;
            stack_.push (num1);
        }
        else if ( currentPlace.head[0] == COMMAND::DIV )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to math in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            num1 = num2 / num1;
            stack_.push (num1);
        }
        else if ( currentPlace.head[0] == COMMAND::JMP )
        {
            index = currentPlace.data;
        }
        else if ( currentPlace.head[0] == COMMAND::J_EQUAL )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to J_X in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            if ( num1 == num2 )
            {
                index = currentPlace.data;
            }
        }
        else if ( currentPlace.head[0] == COMMAND::J_ABOVE )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to J_X in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            if ( num1 > num2 )
            {
                index = currentPlace.data;
            }
        }
        else if ( currentPlace.head[0] == COMMAND::J_BELOW )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to J_X in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            if ( num1 < num2 )
            {
                index = currentPlace.data;
            }
        }
        else if ( currentPlace.head[0] == COMMAND::J_NOT_BE )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to J_X in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            if ( num1 <= num2 )
            {
                index = currentPlace.data;
            }
        }
        else if ( currentPlace.head[0] == COMMAND::J_NOT_AB )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to J_X in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            if ( num1 >= num2 )
            {
                index = currentPlace.data;
            }
        }
        else if ( currentPlace.head[0] == COMMAND::J_NOT_EQ )
        {
            if ( stack_.size () < 2 )
            {
                printf ("Trying to J_X in less than 2 entries stack\n");
                return false;
            }
            double num1 = stack_.top ();
            stack_.pop ();
            double num2 = stack_.top ();
            stack_.pop ();
            if ( num1 != num2 )
            {
                index = currentPlace.data;
            }
        }
        else if ( currentPlace.head[0] == COMMAND::MARK )
        {
        }
        else if ( currentPlace.head[0] == COMMAND::CALL )
        {
            callStack_.push (index);
            index = currentPlace.data;
        }
        else if ( currentPlace.head[0] == COMMAND::RET )
        {
            if ( callStack_.size () < 1 )
            {
                printf ("Trying to ret with empty return stack\n");
                return false;
            }
            index = callStack_.top ();
            callStack_.pop ();
        }
        else if ( currentPlace.head[0] == COMMAND::IN )
        {
            double input = 0;
            printf ("Requested input:");
            scanf ("%lf", &input);
            reg_[currentPlace.head[2]] = input;
        }
        else if ( currentPlace.head[0] == COMMAND::OUT )
        {
            printf ("Requested output:%f\n", reg_[currentPlace.head[2]]);
        }
        else
        {
            printf ("Unknown command reached:%d !\n", currentPlace.head[0]);
            return false;
        }
        index++;
    }
    return true;
}
