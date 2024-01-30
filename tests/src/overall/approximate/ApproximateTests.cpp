#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"

using namespace fintamath;

TEST(ApproximateTests, approximateTest) {
  EXPECT_EQ(approximate(Expression("150!")).toString(),
            "5.7133839564458545904789328652610540031895535786011264182548375833179829124845398*10^262");
  EXPECT_EQ(approximate(Expression("E")).toString(),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
  EXPECT_EQ(approximate(Expression("Pi")).toString(),
            "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
  EXPECT_EQ(approximate(Expression("exp100")).toString(),
            "26881171418161354484126255515800135873611118.773741922415191608615280287034909565");
  EXPECT_EQ(approximate(Expression("E^101")).toString(),
            "73070599793680672726476826340615135890078390.083960707616445859670987728609198428");
  EXPECT_EQ(approximate(Expression("E^(-101)")).toString(),
            "1.3685394711738530002470557302322944177986775531612023009807438134142551921153897*10^-44");
  EXPECT_EQ(approximate(Expression("ln3")).toString(),
            "1.098612288668109691395245236922525704647490557822749451734694333637494293218609");
  EXPECT_EQ(approximate(Expression("ln2")).toString(),
            "0.69314718055994530941723212145817656807550013436025525412068000949339362196969472");
  EXPECT_EQ(approximate(Expression("ln100")).toString(),
            "4.605170185988091368035982909368728415202202977257545952066655801935145219354705");
  EXPECT_EQ(approximate(Expression("lg99")).toString(),
            "1.9956351945975499153402557777532548601069599188478448242562702992902113378005716");
  EXPECT_EQ(approximate(Expression("lg100")).toString(),
            "2");
  EXPECT_EQ(approximate(Expression("lb100")).toString(),
            "6.6438561897747246957406388589787803517296627860491612241095127916318695532172504");
  EXPECT_EQ(approximate(Expression("lb4")).toString(),
            "2");
  EXPECT_EQ(approximate(Expression("sin10")).toString(),
            "-0.54402111088936981340474766185137728168364301291622389157418401261675720964049343");
  EXPECT_EQ(approximate(Expression("cos10")).toString(),
            "-0.83907152907645245225886394782406483451993016513316854683595373104879258686627077");
  EXPECT_EQ(approximate(Expression("tan10")).toString(),
            "0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(approximate(Expression("cot10")).toString(),
            "1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_EQ(approximate(Expression("sec10")).toString(),
            "-1.1917935066878958108796938984273465902047299220035186727706136445417481901426913");
  EXPECT_EQ(approximate(Expression("csc10")).toString(),
            "-1.8381639608896655887052365237649145973889020018834973862573493747201515058875292");
  EXPECT_EQ(approximate(Expression("asin0.9")).toString(),
            "1.1197695149986341866866770558453996158951621864033028823756818639144375371065333");
  EXPECT_EQ(approximate(Expression("acos0.9")).toString(),
            "0.45102681179626243254464463579435182620342251328425002811179043223947066603657116");
  EXPECT_EQ(approximate(Expression("atan10")).toString(),
            "1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_EQ(approximate(Expression("acot10")).toString(),
            "0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");
  EXPECT_EQ(approximate(Expression("asec10")).toString(),
            "1.4706289056333368228857985121870581235299087274579233690964484411175055294922419");
  EXPECT_EQ(approximate(Expression("acsc10")).toString(),
            "0.10016742116155979634552317945269331856867597222962954139102385503640267365086255");
  EXPECT_EQ(approximate(Expression("sinh10")).toString(),
            "11013.232874703393377236524554846364402901451190319346103835228548076948583785685");
  EXPECT_EQ(approximate(Expression("cosh10")).toString(),
            "11013.232920103323139721376090437879963452061428237434970400197807148254234785107");
  EXPECT_EQ(approximate(Expression("tanh10")).toString(),
            "0.99999999587769276361959283713827574105081461849501996226140069543680188089876683");
  EXPECT_EQ(approximate(Expression("coth10")).toString(),
            "1.0000000041223072533738241840280803124601800267562193084479187641100667185123807");
  EXPECT_EQ(approximate(Expression("sech10")).toString(),
            "9.0799859337817244080129507820478187068803766001825381516397080560420174468338146*10^-5");
  EXPECT_EQ(approximate(Expression("csch10")).toString(),
            "9.0799859712122162833736493607291370367410765671445711489891847505702178459640405*10^-5");
  EXPECT_EQ(approximate(Expression("asinh0.9")).toString(),
            "0.80886693565278246250935016738160604299699494260611658590774273687832265593746445");
  EXPECT_EQ(approximate(Expression("acosh1.9")).toString(),
            "1.2571958266003804345446952305599900185447096920846764166114358405852412800661934");
  EXPECT_EQ(approximate(Expression("atanh0.9")).toString(),
            "1.4722194895832202300045137159439267686186896306495644092689801182046463510320986");
  EXPECT_EQ(approximate(Expression("acoth1.9")).toString(),
            "0.5850356263251273221963907792584300980997658991386225877261408421838960973503172");
  EXPECT_EQ(approximate(Expression("asech0.9")).toString(),
            "0.46714530810326201812838149166592294470091920423633277925539967947899330501299865");
  EXPECT_EQ(approximate(Expression("acsch1.9")).toString(),
            "0.50462466551048371741604715782227695355849782672942308840662278634723539375892107");
  EXPECT_EQ(approximate(Expression("((2))*sqrt2")).toString(),
            "2.8284271247461900976033774484193961571393437507538961463533594759814649569242141");
  EXPECT_EQ(approximate(Expression("sqrt2*((2))")).toString(),
            "2.8284271247461900976033774484193961571393437507538961463533594759814649569242141");
  EXPECT_EQ(approximate(Expression("sin(1)^2")).toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(approximate(Expression("sin(-1)^2")).toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(approximate(Expression("sin1^2")).toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(approximate(Expression("sin(10^30)")).toString(),
            "-0.090116901912138058030386428952987330274396332993043449885460666579773983476795775");
  EXPECT_EQ(approximate(Expression("sin(Pi/3)")).toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(approximate(Expression("cos(Pi/3)")).toString(),
            "0.5");
  EXPECT_EQ(approximate(Expression("2!*E")).toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");
  EXPECT_EQ(approximate(Expression("E*2!")).toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");
  EXPECT_EQ(approximate(Expression("sqrt((1-cos(2*(Pi/3)))/2)")).toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(approximate(Expression("2*sqrt((1-cos(2*(Pi/3)))/2)*cos(Pi/3)")).toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(approximate(Expression("1/(sin(5))")).toString(),
            "-1.0428352127714058197831198559077598439723517523645461744044708582222288573346961");
  EXPECT_EQ(approximate(Expression("sin(60deg)")).toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(approximate(Expression("log(500!, 500! + 1)")).toString(), "1.0");

  EXPECT_EQ(approximate(Expression("E^(E^(E^(E^(E^E))))")).toString(),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476^(2."
            "7182818284590452353602874713526624977572470936999595749669676277240766303535476^(2."
            "3315043990071954622896899110121376663320174289635168232800545468180794366424973*10^1656520))");

  EXPECT_EQ(approximate(Expression("sin(floor(E^10))")).toString(),
            "-0.28969263040207500615366554669422425489060452363910610917250538601423874640051459");
  EXPECT_EQ(approximate(Expression("sin(ceil(E^10))")).toString(),
            "-0.96191007900804641383913232250486113391226136975674660918707766984049730795121162");
  EXPECT_EQ(approximate(Expression("cos(floor(11^10))")).toString(),
            "-0.4398324432476489878621537810397255512584110903388962591029029773506989984056853");
  EXPECT_EQ(approximate(Expression("cos(ceil(11^10))")).toString(),
            "-0.4398324432476489878621537810397255512584110903388962591029029773506989984056853");
  EXPECT_EQ(approximate(Expression("ln(floor(E^10))")).toString(),
            "9.9999788527248892938130978462467834105024172271892998574080180654845967473754541");
  EXPECT_EQ(approximate(Expression("root(ceil(E^10), 3)")).toString(),
            "28.031851508556071101342707542030481102710581537531050303928482414307208991692382");
  EXPECT_EQ(approximate(Expression("ln(floor(11^10))")).toString(),
            "23.978952727983705440619435779651292998217068539374171752185677091305736239132367");
  EXPECT_EQ(approximate(Expression("root(ceil(11^10), 3)")).toString(),
            "2960.117500547758958671098654417191228566388539497004587135829271326993708483441");

  EXPECT_EQ(approximate(Expression("(2/3)!")).toString(),
            "0.90274529295093361129685868543634252367955151070452913226268164530918864360116169");
  EXPECT_EQ(approximate(Expression("E!")).toString(),
            "4.2608204763570033817001212246457024649334243739593219749116048935993443487275001");
  EXPECT_EQ(approximate(Expression("(2/3)!!")).toString(),
            "0.66666666666666666666666666666666666666666666666666666666666666666666666666666667!!");
  EXPECT_EQ(approximate(Expression("(1/1000000000000000000000000000000000000000)!!")).toString(),
            "(1.0*10^-39)!!");
  EXPECT_EQ(approximate(Expression("(-1)!!")).toString(),
            "(-1)!!");

  EXPECT_EQ(approximate(Expression("I")).toString(),
            "I");
  EXPECT_EQ(approximate(Expression("5 + I")).toString(),
            "5 + I");
  EXPECT_EQ(approximate(Expression("5 I")).toString(),
            "5 I");
  EXPECT_EQ(approximate(Expression("5 + 5 I")).toString(),
            "5 + 5 I");
  EXPECT_EQ(approximate(Expression("5/2 + 1/2 I")).toString(),
            "2.5 + 0.5 I");
  EXPECT_EQ(approximate(Expression("5 + 1/2 I")).toString(),
            "5 + 0.5 I");
  EXPECT_EQ(approximate(Expression("5/2 + 2 I")).toString(),
            "2.5 + 2 I");
  EXPECT_EQ(approximate(Expression("5/I")).toString(),
            "-5 I");
  EXPECT_EQ(approximate(Expression("E/I")).toString(),
            "-2.7182818284590452353602874713526624977572470936999595749669676277240766303535476 I");
  EXPECT_EQ(approximate(Expression("-I")).toString(),
            "-I");
  EXPECT_EQ(approximate(Expression("5 - I")).toString(),
            "5 - I");
  EXPECT_EQ(approximate(Expression("5 - I")).toString(),
            "5 - I");
  EXPECT_EQ(approximate(Expression("5 - 5 I")).toString(),
            "5 - 5 I");
  EXPECT_EQ(approximate(Expression("5/2 - 1/2 I")).toString(),
            "2.5 - 0.5 I");
  EXPECT_EQ(approximate(Expression("5 - 1/2 I")).toString(),
            "5 - 0.5 I");
  EXPECT_EQ(approximate(Expression("5/2 - 2 I")).toString(),
            "2.5 - 2 I");
  EXPECT_EQ(approximate(Expression("5/-I")).toString(),
            "5 I");
  EXPECT_EQ(approximate(Expression("E/-I")).toString(),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476 I");
  EXPECT_EQ(approximate(Expression("sin(I)")).toString(),
            "sin(I)");
  EXPECT_EQ(approximate(Expression("sin(5 + I)")).toString(),
            "sin(5 + I)");
  EXPECT_EQ(approximate(Expression("sin(5/2 + 1/2 I)")).toString(),
            "sin(2.5 + 0.5 I)");
  EXPECT_EQ(approximate(Expression("ln(I + 1)")).toString(),
            "ln(1 + I)");

  EXPECT_EQ(approximate(Expression("ln(x)")).toString(),
            "ln(x)");
  EXPECT_EQ(approximate(Expression("lb(x)")).toString(),
            "log(2, x)");
  EXPECT_EQ(approximate(Expression("sqrt(x)")).toString(),
            "sqrt(x)");
  EXPECT_EQ(approximate(Expression("root(x, 3)")).toString(),
            "root(x, 3)");
  EXPECT_EQ(approximate(Expression("root(x, 10)")).toString(),
            "x^0.1");
  EXPECT_EQ(approximate(Expression("root(x, 33)")).toString(),
            "x^0.03030303030303030303030303030303030303030303030303030303030303030303030303030303");

  EXPECT_EQ(approximate(Expression("ln(9/40) a + 1 > 0")).toString(),
            "a - 0.67039636015551187562980441234433718448357469016083894454851276080981791123695912 < 0");
  EXPECT_EQ(approximate(Expression("-a + Pi^4 sqrt(2) a < 0")).toString(),
            "a < 0");
  EXPECT_EQ(approximate(Expression("-a + Pi^4 sqrt(2) a - sqrt(3) a < 0")).toString(),
            "a < 0");
  EXPECT_EQ(approximate(Expression("-a + Pi^4 sqrt(2) a - sqrt(3) a + 1 < 0")).toString(),
            "a + 0.0074060245747335632557466509014062540940313639927954137165613831918681276157723614 < 0");
}

TEST(ApproximateTests, approxamateSpecialValuesTest) {
  EXPECT_EQ(approximate(Expression("1 / (1 - tanh(11^10))")).toString(), "cosh(25937424601)/(cosh(25937424601) - sinh(25937424601))");
  EXPECT_EQ(approximate(Expression("1 / (1 - coth(11^10))")).toString(), "sinh(25937424601)/(sinh(25937424601) - cosh(25937424601))");
  EXPECT_EQ(approximate(Expression("1 / (ln(2)^10000000000000)")).toString(), "1/0.0");

  EXPECT_EQ(approximate(Expression("sqr(ln(2)^10000000000000)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("root(ln(2)^10000000000000, 3)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("sin(ln(2)^10000000000000)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("cos(ln(2)^10000000000000)")).toString(), "1.0");
  EXPECT_EQ(approximate(Expression("tan(ln(2)^10000000000000)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("cot(ln(2)^10000000000000)")).toString(), "cot(0.0)");
  EXPECT_EQ(approximate(Expression("sec(ln(2)^10000000000000)")).toString(), "1.0");
  EXPECT_EQ(approximate(Expression("csc(ln(2)^10000000000000)")).toString(), "csc(0.0)");
  EXPECT_EQ(approximate(Expression("asin(ln(2)^10000000000000)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("acos(ln(2)^10000000000000)")).toString(), "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(approximate(Expression("atan(ln(2)^10000000000000)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("acot(ln(2)^10000000000000)")).toString(), "acot(0.0)");
  EXPECT_EQ(approximate(Expression("asec(ln(2)^10000000000000)")).toString(), "asec(0.0)");
  EXPECT_EQ(approximate(Expression("acsc(ln(2)^10000000000000)")).toString(), "acsc(0.0)");
  EXPECT_EQ(approximate(Expression("sinh(ln(2)^10000000000000)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("cosh(ln(2)^10000000000000)")).toString(), "1.0");
  EXPECT_EQ(approximate(Expression("tanh(ln(2)^10000000000000)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("coth(ln(2)^10000000000000)")).toString(), "coth(0.0)");
  EXPECT_EQ(approximate(Expression("sech(ln(2)^10000000000000)")).toString(), "1.0");
  EXPECT_EQ(approximate(Expression("csch(ln(2)^10000000000000)")).toString(), "csch(0.0)");
  EXPECT_EQ(approximate(Expression("asinh(ln(2)^10000000000000)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("acosh(ln(2)^10000000000000)")).toString(), "acosh(0.0)");
  EXPECT_EQ(approximate(Expression("atanh(ln(2)^10000000000000)")).toString(), "0.0");
  EXPECT_EQ(approximate(Expression("acoth(ln(2)^10000000000000)")).toString(), "acoth(0.0)");
  EXPECT_EQ(approximate(Expression("asech(ln(2)^10000000000000)")).toString(), "asech(0.0)");
  EXPECT_EQ(approximate(Expression("acsch(ln(2)^10000000000000)")).toString(), "acsch(0.0)");

  EXPECT_EQ(approximate(Expression("sqrt(-ln(2)^10000000000000)")).toString(), "sqrt(-0.0)");
  EXPECT_EQ(approximate(Expression("root(-ln(2)^10000000000000, 3)")).toString(), "root(-0.0, 3)");
  EXPECT_EQ(approximate(Expression("sin(-ln(2)^10000000000000)")).toString(), "-0.0");
  EXPECT_EQ(approximate(Expression("cos(-ln(2)^10000000000000)")).toString(), "1.0");
  EXPECT_EQ(approximate(Expression("tan(-ln(2)^10000000000000)")).toString(), "-0.0");
  EXPECT_EQ(approximate(Expression("cot(-ln(2)^10000000000000)")).toString(), "-cot(0.0)");
  EXPECT_EQ(approximate(Expression("sec(-ln(2)^10000000000000)")).toString(), "1.0");
  EXPECT_EQ(approximate(Expression("csc(-ln(2)^10000000000000)")).toString(), "-csc(0.0)");
  EXPECT_EQ(approximate(Expression("asin(-ln(2)^10000000000000)")).toString(), "-0.0");
  EXPECT_EQ(approximate(Expression("acos(-ln(2)^10000000000000)")).toString(), "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(approximate(Expression("atan(-ln(2)^10000000000000)")).toString(), "-0.0");
  EXPECT_EQ(approximate(Expression("acot(-ln(2)^10000000000000)")).toString(), "acot(-0.0)");
  EXPECT_EQ(approximate(Expression("asec(-ln(2)^10000000000000)")).toString(), "asec(-0.0)");
  EXPECT_EQ(approximate(Expression("acsc(-ln(2)^10000000000000)")).toString(), "acsc(-0.0)");
  EXPECT_EQ(approximate(Expression("sinh(-ln(2)^10000000000000)")).toString(), "-0.0");
  EXPECT_EQ(approximate(Expression("cosh(-ln(2)^10000000000000)")).toString(), "1.0");
  EXPECT_EQ(approximate(Expression("tanh(-ln(2)^10000000000000)")).toString(), "-0.0");
  EXPECT_EQ(approximate(Expression("coth(-ln(2)^10000000000000)")).toString(), "-coth(0.0)");
  EXPECT_EQ(approximate(Expression("sech(-ln(2)^10000000000000)")).toString(), "1.0");
  EXPECT_EQ(approximate(Expression("csch(-ln(2)^10000000000000)")).toString(), "-csch(0.0)");
  EXPECT_EQ(approximate(Expression("asinh(-ln(2)^10000000000000)")).toString(), "-0.0");
  EXPECT_EQ(approximate(Expression("acosh(-ln(2)^10000000000000)")).toString(), "acosh(-0.0)");
  EXPECT_EQ(approximate(Expression("atanh(-ln(2)^10000000000000)")).toString(), "-0.0");
  EXPECT_EQ(approximate(Expression("acoth(-ln(2)^10000000000000)")).toString(), "acoth(-0.0)");
  EXPECT_EQ(approximate(Expression("asech(-ln(2)^10000000000000)")).toString(), "asech(-0.0)");
  EXPECT_EQ(approximate(Expression("acsch(-ln(2)^10000000000000)")).toString(), "acsch(-0.0)");

  EXPECT_EQ(approximate(Expression("floor(ln(2)^10000000000000)")).toString(), "floor(0.0)");
  EXPECT_EQ(approximate(Expression("ceil(ln(2)^10000000000000)")).toString(), "ceil(0.0)");
  EXPECT_EQ(approximate(Expression("sign(ln(2)^10000000000000)")).toString(), "1");
  EXPECT_EQ(approximate(Expression("floor(1 - ln(2)^10000000000000)")).toString(), "-ceil(-1.0)");
  EXPECT_EQ(approximate(Expression("ceil(1 - ln(2)^10000000000000)")).toString(), "-floor(-1.0)");
  EXPECT_EQ(approximate(Expression("sign(1 - ln(2)^10000000000000)")).toString(), "1");

  EXPECT_EQ(approximate(Expression("floor(ln(2)^10000000000000 * sin(4))")).toString(), "floor(-0.0)");
  EXPECT_EQ(approximate(Expression("ceil(ln(2)^10000000000000 * sin(4))")).toString(), "ceil(-0.0)");
  EXPECT_EQ(approximate(Expression("sign(ln(2)^10000000000000 * sin(4))")).toString(), "-1");
  EXPECT_EQ(approximate(Expression("floor(1 - ln(2)^10000000000000 * sin(4))")).toString(), "-ceil(-1.0)");
  EXPECT_EQ(approximate(Expression("ceil(1 - ln(2)^10000000000000 * sin(4))")).toString(), "-floor(-1.0)");
  EXPECT_EQ(approximate(Expression("sign(1 - ln(2)^10000000000000 * sin(4))")).toString(), "1");

  EXPECT_EQ(approximate(Expression("floor(ln(2)^10000000000000 * (sin(4) + 1 - 1))")).toString(), "floor(-0.0)");
  EXPECT_EQ(approximate(Expression("ceil(ln(2)^10000000000000 * (sin(4) + 1 - 1))")).toString(), "ceil(-0.0)");
  EXPECT_EQ(approximate(Expression("sign(ln(2)^10000000000000 * (sin(4) + 1 - 1))")).toString(), "-1");
  EXPECT_EQ(approximate(Expression("floor(1 - ln(2)^10000000000000 * (sin(4) + 1 - 1))")).toString(), "-ceil(-1.0)");
  EXPECT_EQ(approximate(Expression("ceil(1 - ln(2)^10000000000000 * (sin(4) + 1 - 1))")).toString(), "-floor(-1.0)");
  EXPECT_EQ(approximate(Expression("sign(1 - ln(2)^10000000000000 * (sin(4) + 1 - 1))")).toString(), "1");

  EXPECT_EQ(approximate(Expression("floor(ln(2)^10000000000000 * (2sin(4) - sin(4)))")).toString(), "floor(-0.0)");
  EXPECT_EQ(approximate(Expression("ceil(ln(2)^10000000000000 * (2sin(4) - sin(4)))")).toString(), "ceil(-0.0)");
  EXPECT_EQ(approximate(Expression("sign(ln(2)^10000000000000 * (2sin(4) - sin(4)))")).toString(), "-1");
  EXPECT_EQ(approximate(Expression("floor(1 - ln(2)^10000000000000 * (2sin(4) - sin(4)))")).toString(), "-ceil(-1.0)");
  EXPECT_EQ(approximate(Expression("ceil(1 - ln(2)^10000000000000 * (2sin(4) - sin(4)))")).toString(), "-floor(-1.0)");
  EXPECT_EQ(approximate(Expression("sign(1 - ln(2)^10000000000000 * (2sin(4) - sin(4)))")).toString(), "1");

  EXPECT_EQ(approximate(Expression("floor(ln(2)^10000000000000 / sin(4))")).toString(), "floor(-0.0)");
  EXPECT_EQ(approximate(Expression("ceil(ln(2)^10000000000000 / sin(4))")).toString(), "ceil(-0.0)");
  EXPECT_EQ(approximate(Expression("sign(ln(2)^10000000000000 / sin(4))")).toString(), "-1");
  EXPECT_EQ(approximate(Expression("floor(1 - ln(2)^10000000000000 / sin(4))")).toString(), "-ceil(-1.0)");
  EXPECT_EQ(approximate(Expression("ceil(1 - ln(2)^10000000000000 / sin(4))")).toString(), "-floor(-1.0)");
  EXPECT_EQ(approximate(Expression("sign(1 - ln(2)^10000000000000 / sin(4))")).toString(), "1");

  EXPECT_EQ(approximate(Expression("floor(ln(2)^10000000000000 / (sin(4) + 1 - 1))")).toString(), "floor(-0.0)");
  EXPECT_EQ(approximate(Expression("ceil(ln(2)^10000000000000 / (sin(4) + 1 - 1))")).toString(), "ceil(-0.0)");
  EXPECT_EQ(approximate(Expression("sign(ln(2)^10000000000000 / (sin(4) + 1 - 1))")).toString(), "-1");
  EXPECT_EQ(approximate(Expression("floor(1 - ln(2)^10000000000000 / (sin(4) + 1 - 1))")).toString(), "-ceil(-1.0)");
  EXPECT_EQ(approximate(Expression("ceil(1 - ln(2)^10000000000000 / (sin(4) + 1 - 1))")).toString(), "-floor(-1.0)");
  EXPECT_EQ(approximate(Expression("sign(1 - ln(2)^10000000000000 / (sin(4) + 1 - 1))")).toString(), "1");

  EXPECT_EQ(approximate(Expression("floor(ln(2)^10000000000000 / (2sin(4) - sin(4)))")).toString(), "floor(-0.0)");
  EXPECT_EQ(approximate(Expression("ceil(ln(2)^10000000000000 / (2sin(4) - sin(4)))")).toString(), "ceil(-0.0)");
  EXPECT_EQ(approximate(Expression("sign(ln(2)^10000000000000 / (2sin(4) - sin(4)))")).toString(), "-1");
  EXPECT_EQ(approximate(Expression("floor(1 - ln(2)^10000000000000 / (2sin(4) - sin(4)))")).toString(), "-ceil(-1.0)");
  EXPECT_EQ(approximate(Expression("ceil(1 - ln(2)^10000000000000 / (2sin(4) - sin(4)))")).toString(), "-floor(-1.0)");
  EXPECT_EQ(approximate(Expression("sign(1 - ln(2)^10000000000000 / (2sin(4) - sin(4)))")).toString(), "1");

  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 = 0")).toString(), "False");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 != 0")).toString(), "True");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 < 0")).toString(), "False");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 > 0")).toString(), "True");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 <= 0")).toString(), "False");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 >= 0")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 = 0")).toString(), "False");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 != 0")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 < 0")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 > 0")).toString(), "False");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 <= 0")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 >= 0")).toString(), "False");

  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 = ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 != ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 < ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 > ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 <= ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 >= ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 = ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 != ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 < ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 > ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 <= ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 >= ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 = -ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 != -ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 < -ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 > -ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 <= -ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("ln(2)^10000000000000 >= -ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 = -ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 != -ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 < -ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 > -ln(2)^100000000")).toString(), "True");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 <= -ln(2)^100000000")).toString(), "False");
  EXPECT_EQ(approximate(Expression("-ln(2)^10000000000000 >= -ln(2)^100000000")).toString(), "True");
}

TEST(ApproximateTests, approximateWithPrecisionTest) {
  EXPECT_EQ(approximate(Expression("123"), 2).toString(), "1.2*10^2");
  EXPECT_EQ(approximate(Expression("123"), 3).toString(), "123");
  EXPECT_EQ(approximate(Expression("999"), 2).toString(), "1.0*10^3");
  EXPECT_EQ(approximate(Expression("999"), 3).toString(), "999");
  EXPECT_EQ(approximate(Expression("1000"), 3).toString(), "1.0*10^3");
  EXPECT_EQ(approximate(Expression("1000"), 4).toString(), "1000");
  EXPECT_EQ(approximate(Expression("2/3"), 0).toString(), "0.7");
  EXPECT_EQ(approximate(Expression("2/3"), 1).toString(), "0.7");
  EXPECT_EQ(approximate(Expression("2/3"), 2).toString(), "0.67");
  EXPECT_EQ(approximate(Expression("10^10000"), 8).toString(), "1.0*10^10000");
  EXPECT_EQ(approximate(Expression("9^10000"), 8).toString(), "2.6613034*10^9542");
  EXPECT_EQ(approximate(Expression("sin(E)"), 16).toString(), "0.4107812905029087");
  EXPECT_EQ(approximate(Expression("sin(E)"), 100).toString(), "0.4107812905029086954760094920183605918883069703934153453045716588061351824376549958759786190454355935");
  EXPECT_EQ(approximate(Expression("sin(E)"), 500).toString(), "0.41078129050290869547600949201836059188830697039341534530457165880613518243765499587597861904543559353998291725993302611025612058214980807451386832166444404531330197030068700843779775501870429268806003976547248700619445558784780526262698913892212813629990839737608068439105974107056580477820375774780424366945910698422961638162689359340566062721679765484253127451162965356964229969288617282831139369276388867344864990496109344825533823527519982767717612020764891885643060371919941565596238925522726933");
  EXPECT_EQ(approximate(Expression("sin(E)"), 1000).toString(), "0.410781290502908695476009492018360591888306970393415345304571658806135182437654995875978619045435593539982917259933026110256120582149808074513868321664444045313301970300687008437797755018704292688060039765472487006194455587847805262626989138922128136299908397376080684391059741070565804778203757747804243669459106984229616381626893593405660627216797654842531274511629653569642299692886172828311393692763888673448649904961093448255338235275199827677176120207648918856430603719199415655962389255227269329528247477565374084254456845493070521764653289529029121531798267980455224152201783074312455247443118659121061166824975283442729765920066115702948819794373441039363621507249342167892877264237554995364981898784098244975928739908684886687169561527095433756282781475277781538970397993742686571201323888405828052948752757923286033258285782682064914566808696556377856800938584299870591049139758903145979548061988835578438108419199725833087967291498589345414792089183496072498118579415411402320500775908443");
  EXPECT_EQ(approximate(Expression("sin(sin(E))"), 30).toString(), "0.39932574404189139297067052142");
  EXPECT_EQ(approximate(Expression("(sqrt(2) + 1)^2"), 5).toString(), "5.8284");
  EXPECT_EQ(approximate(Expression("E/I"), 5).toString(), "-2.7183 I");
  EXPECT_EQ(approximate(Expression("E/-I"), 5).toString(), "2.7183 I");
  EXPECT_EQ(approximate(Expression("x+E"), 8).toString(), "x + 2.7182818");
  EXPECT_EQ(approximate(Expression("x^(100!)"), 8).toString(), "x^(9.3326215*10^157)");
  EXPECT_EQ(approximate(Expression("2^200/x"), 10).toString(), "(1.606938044*10^60)/x");
  EXPECT_EQ(approximate(Expression("x/2^200"), 10).toString(), "6.223015278*10^-61 x");
  EXPECT_EQ(approximate(Expression("(sqrt(2) - a - 1)^2"), 5).toString(), "a^2 - 0.82843 a + 0.17157");
  EXPECT_EQ(approximate(Expression("2 sqrt2 sin3 a + 3 ln5 root(2, 3) b"), 5).toString(), "0.39915 a + 6.0833 b");

  EXPECT_EQ(approximate(approximate(Expression("sin(5)"), 100), 5).toString(), "-0.95892");
  EXPECT_EQ(approximate(approximate(Expression("sin(5) I"), 100), 5).toString(), "-0.95892 I");
  EXPECT_EQ(approximate(approximate(Expression("I + sin(4)"), 100), 5).toString(), "-0.7568 + I");
  EXPECT_EQ(approximate(approximate(Expression("sin(5) I + sin(4)"), 100), 5).toString(), "-0.7568 - 0.95892 I");

  {
    Expression expr = approximate(Expression("cos(5)"), 56);
    EXPECT_EQ(expr.toString(), "0.28366218546322626446663917151355730833442259225221594493");

    expr = approximate(expr, 55);
    EXPECT_EQ(expr.toString(), "0.2836621854632262644666391715135573083344225922522159449");

    expr = approximate(expr, 1);
    EXPECT_EQ(expr.toString(), "0.3");
  }
}
