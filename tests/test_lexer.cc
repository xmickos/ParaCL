#include <gtest/gtest.h>
#include "../src/main_definitives.hpp"
#include "../src/utils.hpp"

TEST(End2End, LexerTest1) {
    CompilationContext ctxt;
    ctxt.src = R"(
        a = ?
        print a;
    )";
    do_lexer_work(ctxt);

    std::vector<Token> ground_truth = {
        Token{TokenKind::Identifier, 9, std::string_view(&ctxt.src[9], 1)},
        Token{TokenKind::Assign, 11, std::string_view(&ctxt.src[11], 1)},
        Token{TokenKind::Input, 13, std::string_view(&ctxt.src[13], 1)},
        Token{TokenKind::PrintKeyword, 23, std::string_view(&ctxt.src[23], 5)},
        Token{TokenKind::Identifier, 29, std::string_view(&ctxt.src[29], 1)},
        Token{TokenKind::Semicolon, 30, std::string_view(&ctxt.src[30], 1)}
    };
    EXPECT_TRUE(std::equal(ctxt.tokens.begin(), ctxt.tokens.end(), ground_truth.begin()));
}

TEST(End2End, LexerTest2) {
    CompilationContext ctxt;
    ctxt.src = R"(
        __b = ?
        __a = @;
        print a + b;
    )";

    EXPECT_DEATH(do_lexer_work(ctxt), "unreachable");
}

TEST(UnitTests, classify_identifier) {
    std::string print1 = "print", print2 = "pritn", print3 = "PRINT";
    std::string if1 = "if", if2 = "fi", if3 = "IF";
    std::string while1 = "while", while2 = "whiel", while3 = "WHILE";

    EXPECT_EQ(classify_identifier(print1), TokenKind::PrintKeyword);
    EXPECT_EQ(classify_identifier(print2), TokenKind::Identifier);
    EXPECT_EQ(classify_identifier(print3), TokenKind::Identifier);

    EXPECT_EQ(classify_identifier(if1), TokenKind::IfKeyword);
    EXPECT_EQ(classify_identifier(if2), TokenKind::Identifier);
    EXPECT_EQ(classify_identifier(if3), TokenKind::Identifier);

    EXPECT_EQ(classify_identifier(while1), TokenKind::WhileKeyword);
    EXPECT_EQ(classify_identifier(while2), TokenKind::Identifier);
    EXPECT_EQ(classify_identifier(while3), TokenKind::Identifier);
}
