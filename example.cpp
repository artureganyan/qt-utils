/******************************************************************************
 * Copyright (c) 2015 Artur Eganyan
 *
 * This software is provided "AS IS", WITHOUT ANY WARRANTY, express or implied.
 ******************************************************************************/

#define EXAMPLE_NAMESPACE(className) className##_example

// Put required class name into EXAMPLE_NAMESPACE() below
#define EXAMPLE EXAMPLE_NAMESPACE(PlaceholderItemDelegate)

namespace EXAMPLE {

extern int main( int argc, char** argv );

}

int main(int argc, char *argv[])
{
    return EXAMPLE::main(argc, argv);
}
