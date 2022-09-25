#include "Scene_introduction.h"
#include "bn_format.h"

namespace Runa::Scene
{

namespace
{
constexpr int MAX_PAGE = 16;
constexpr int LINES_PER_PAGE = 9;
constexpr bn::string_view INTRO_LIST[LINES_PER_PAGE * MAX_PAGE] = {
    " Hunt for chocolates!",
    "",
    "Chocolate hunter Runa is",
    "addicted to chocolate.",
    "Help her earn chocolate",
    "through battle.",
    "",
    "",
    "",

    " In the camp (1):",
    "",
    "Runa must eat enough chocolate",
    "in a certain amount of time.",
    "She can extend her lifespan",
    "only if she eat chocolates.",
    "",
    "",
    "",

    " In the camp (2):",
    "",
    "She can make potions by",
    "extracting ingredients from ",
    "chocolate to recover her health.",
    "But she cannot restore her life",
    "with potions.",
    "",
    "",

    " In the camp (3):",
    "",
    "Upgrading equipments by",
    "special magic costs a lot of",
    "chocolate, but it is worth it.",
    "Weapon and armor can be upgraded.",
    "",
    "",
    "",

    " In the crossroad (1):",
    "",
    "After each battle, you can choose",
    "one of the three paths to proceed.",
    "Each path contains series of",
    "battles.",
    "",
    "",
    "",

    " In the crossroad (2):",
    "",
    "You can check the total number",
    "of battles (S), the number of",
    "enemies (E), amount of chocolate",
    "enemies have (C).",
    "",
    "",
    "",

    " In the battlefield (1):",
    "",
    "She can fight with",
    "two types of attack.",
    "Melee type attack is physical",
    "element attack.",
    "It costs nothing, but weak.",
    "",
    "",

    " In the battlefield (2):",
    "",
    "She can use various magic to",
    "strengthen herself or",
    "attack the enemies.",
    "Most magic consumes mana.",
    "She learns one spell at each level.",
    "",
    "",

    " In the battlefield (3):",
    "",
    "At the end of the battle,",
    "chocolates and experiences",
    "are gained.",
    "The multiplier of the chocolates",
    "to get will decrease after",
    "every battle sequence.",
    "",

    " In the battlefield (4):",
    "",
    "When the boss of stratum is",
    "defeated, game will proceed",
    "to next stratum, and",
    "chocolate multiplier is recovered.",
    "",
    "",
    "",

    " Game over:",
    "",
    "When health reaches zero or",
    "lifespan (turns) is over,",
    "the game ends.",
    "You can see your current game's",
    "score and your best record ever.",
    "",
    "",

    " Elements:",
    "",
    "There are four types of elements:",
    "physical, fire, ice and lightning.",
    "All enemies have resistance or",
    "weakness for each element.",
    "Each attack has its element type.",
    "",
    "",

    " Status effects:",
    "",
    "Some attacks have the chance to",
    "cause status effects.",
    "Types of status effects include",
    "raising/lowering stats, charge,",
    "guard, etc.",
    "",
    "",

    " Codexes:",
    "",
    "From the options menu,",
    "you can read the codexes for",
    "the enemies encountered and",
    "the spells learned.",
    "",
    "",
    "",

    " Tips (1):",
    "",
    "Each enemy has its own weaknesses",
    "and behavioral patterns.",
    "Based on this information, you can",
    "gain the upper hand in battle.",
    "",
    "",
    "",

    " Tips (2):",
    "",
    "Avoiding enemies too much makes it",
    "difficult to deal with the boss later.",
    "It can be advantageous to take out",
    "as many enemies as possible in",
    "your current state.",
    "",
    "",
};
constexpr int INTRO_X = -110;
constexpr int INTRO_Y = -64;
constexpr int INTRO_Y_INT = 12;

} // namespace

Introduction::Introduction(bn::sprite_text_generator& text_generator) :
    _text_generator(text_generator),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
{
    Effect::Print_text(_text_generator, true, Effect::Alignment::Left, INTRO_X, INTRO_Y + INTRO_Y_INT * 10, INTRO_Y_INT,
                       _sub_text, 2, "Press left or right key to", "switch page, B to return");
    for (bn::sprite_ptr& text_sprite : _sub_text)
    {
        text_sprite.set_blending_enabled(true);
    }
    Print_text();
    _scene_start.Start();
}
Introduction::~Introduction() {}

bn::optional<Scene_Type> Introduction::Update()
{
    switch (_scene_start.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_start.Update();
        break;
    case Effect::State::Done:
        switch (_scene_end.Get_state())
        {
        case Effect::State::Waiting:
            if (bn::keypad::right_pressed())
            {
                if (++_current_page == MAX_PAGE) { --_current_page; }
                else
                {
                    bn::sound_items::sfx_menu_move.play();
                    Print_text();
                }
            }
            else if (bn::keypad::left_pressed())
            {
                if (--_current_page < 0) { ++_current_page; }
                else
                {
                    bn::sound_items::sfx_menu_move.play();
                    Print_text();
                }
            }
            else if (bn::keypad::b_pressed())
            {
                bn::sound_items::sfx_menu_cancelled.play();
                _scene_end.Start();
            }
            break;
        case Effect::State::Ongoing:
            _scene_end.Update();
            break;
        case Effect::State::Done:
            return Scene_Type::Title;
            break;
        default: break;
        }
        break;
    default: break;
    }
    return bn::nullopt;
}

void Introduction::Print_text()
{
    _intro_text.clear();
    _text_generator.set_left_alignment();
    for (int i = 0; i < LINES_PER_PAGE; i++)
    {
        _text_generator.generate(INTRO_X, INTRO_Y + INTRO_Y_INT * i, INTRO_LIST[i + LINES_PER_PAGE * _current_page], _intro_text);
    }
    _page_text.clear();
    _text_generator.set_right_alignment();
    _text_generator.generate(112, INTRO_Y + INTRO_Y_INT * 11, bn::format<14>("< {} / {} >", _current_page+1, MAX_PAGE), _page_text);
    for (bn::sprite_ptr& text_sprite : _intro_text)
    {
        text_sprite.set_blending_enabled(true);
    }
    for (bn::sprite_ptr& text_sprite : _page_text)
    {
        text_sprite.set_blending_enabled(true);
    }
}

} // namespace Runa::Scene
