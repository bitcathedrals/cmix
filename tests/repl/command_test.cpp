#include <string>

#include <gtest/gtest.h>

#include <repl/command.h>

TEST(Dispatch, StringToCommand) {
    EXPECT_EQ(string_to_command("quit"), Command::quit);
    EXPECT_EQ(string_to_command("read"), Command::read);
    EXPECT_EQ(string_to_command("write"), Command::write);
}

TEST(Dispatch, LookupCommandEntry) {
    EXPECT_EQ(lookup_command(Command::read).word_count, 1);
}
