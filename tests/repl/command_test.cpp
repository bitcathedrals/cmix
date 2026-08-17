#include <string>

#include <gtest/gtest.h>

#include "repl/command.h"

TEST(CommandDispatch, StringToCommand) {
    EXPECT_EQ(string_to_command("q"), Command::quit);
    EXPECT_EQ(string_to_command("r"), Command::read);
    EXPECT_EQ(string_to_command("w"), Command::write);
    EXPECT_EQ(string_to_command("?"), Command::help);
}

TEST(CommandDispatch, LookupCommandEntry) {
    EXPECT_EQ(lookup_command(Command::read).word_count, 1);
}
