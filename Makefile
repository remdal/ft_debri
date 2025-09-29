###############################################################
#                                         +       +           #
#      File: Makefile            +++     +++				  #
#                                         +       +           #
#       By: Laboitederemdal                +       +          #
#                                        +           +        #
#       Created: 19/09/2025 16:48:39      + + + + + +         #
#                                                             #
###############################################################

CXX			=	clang++ -x objective-c++
CC			=	clang
NAME		=	ft_débri
SRCS		=	Application Renderer
INCLUDES	=	includes
CPP_FILES	=	$(shell find $(SRCS) -name '*.cpp')
C_FILES		=	$(shell find $(SRCS) -name '*.c')
MM_FILES	=	$(shell find $(SRCS) -name '*.mm')
M_FILES		=	$(shell find $(SRCS) -name '*.m')
HEADERS_H	=	$(shell find $(INCLUDES) -name '*.h')
HEADERS_HPP	=	$(shell find $(INCLUDES) -name '*.hpp')
CFLAGS		=	-I./includes -Wall -Wextra -Werror
OBJS_DIR	=	Product
DEPS_DIR	=	$(OBJS_DIR)
PLIST		=	application/macOS/Info.plist
FLAGS		=	-std=c++20 -ObjC++ -I./includes -I./Frameworks/metal-cpp -I./Frameworks/metal-cpp-extensions -ferror-limit=10 -fobjc-weak -Warc-bridge-casts-disallowed-in-nonarc #-Wall -Wextra -Werror -fobjc-arc
LINKERFLAGS	=	-Xlinker -sectcreate -Xlinker __TEXT -Xlinker __info_plist -Xlinker $(PLIST)

CPP_OBJS	=	$(patsubst $(SRCS)/%.cpp,$(OBJS_DIR)/%.o,$(CPP_FILES))
C_OBJS		=	$(patsubst $(SRCS)/%.c,$(OBJS_DIR)/%.o,$(C_FILES))
MM_OBJS		=	$(patsubst $(SRCS)/%.mm,$(OBJS_DIR)/%.o,$(MM_FILES))
M_OBJS		=	$(patsubst $(SRCS)/%.m,$(OBJS_DIR)/%.o,$(M_FILES))
$(shell mkdir -p $(sort $(dir $(C_OBJS))) $(sort $(dir $(CPP_OBJS))) $(sort $(dir $(MM_OBJS))) $(sort $(dir $(M_OBJS))))
C_DEPS		=	$(patsubst $(OBJS_DIR)/%.o,$(DEPS_DIR)/%.d,$(C_OBJS))
CPP_DEPS	=	$(patsubst $(OBJS_DIR)/%.o,$(DEPS_DIR)/%.d,$(CPP_OBJS))
MM_DEPS		=	$(patsubst $(OBJS_DIR)/%.o,$(DEPS_DIR)/%.d,$(MM_OBJS))
M_DEPS		=	$(patsubst $(OBJS_DIR)/%.o,$(DEPS_DIR)/%.d,$(M_OBJS))
DEP_FILES	=	$(CPP_DEPS) $(C_DEPS) $(MM_DEPS) $(M_DEPS)
$(shell mkdir -p $(sort $(dir $(DEP_FILES))))

_GREEN		=	\033[92;5;118m
_YELLOW		=	\033[93;5;226m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
CYAN		=	\033[96m
RESET		=	\033[0m
CURSIVE     =	\033[33;3m
GRAY        =	\033[33;2;37m

VPATH=./metal-cpp
vpath %.cpp $(SRCS)
vpath %.c $(SRCS)
vpath %.mm $(SRCS)
vpath %.m $(SRCS)

FRAMEWORKS	=	Metal MetalKit QuartzCore AppKit Foundation GameController Cocoa CoreHaptics CoreMotion PHASE AVFAudio MetalFX CoreText CoreGraphics
LDFLAGS		=	$(addprefix -framework , $(FRAMEWORKS))
MACOS_SDK	=	$(shell xcrun --sdk macosx --show-sdk-path)
CXXFLAGS	+=	-isysroot $(MACOS_SDK)
CFLAGS		+=	-isysroot $(MACOS_SDK)

$(OBJS_DIR)/%.o: %.c
	@ echo "\t$(_YELLOW) compiling... $*.c$(RESET)"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: %.cpp
	@ echo "\t$(_YELLOW) compiling... $*.cpp$(RESET)"
	$(CXX) $(FLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: %.mm #$(SRCS_DIR)/%.mm $(HEADERS_H)
	@ echo "\t$(_YELLOW) compiling... $*.mm$(RESET)"
	$(CXX) $(FLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: %.m
	@ echo "\t$(_YELLOW) compiling... $*.m$(RESET)"
	$(CC) $(FLAGS) -c $< -o $@

$(DEPS_DIR)/%.d: $(SRCS_DIR)/%.cpp | $(DEPS_DIR)
	@ echo "\t$(_YELLOW) compiling... cpp $*.d$(RESET)"
	$(CXX) $(FLAGS) -MM $< -MT $(@:.d=.o) -MF $@

$(DEPS_DIR)/%.d: $(SRCS_DIR)/%.c | $(DEPS_DIR)
	@ echo "\t$(_YELLOW) compiling... $*.d$(RESET)"
	$(CC) $(FLAGS) -MM $< -MT $(@:.d=.o) -MF $@

$(DEPS_DIR)/%.d: $(SRCS_DIR)/%.mm | $(DEPS_DIR)
	@ echo "\t$(_YELLOW) compiling... $*.d$(RESET)"
	$(CXX) $(FLAGS) -MM $< -MT $(@:.d=.o) -MF $@

$(DEPS_DIR)/%.d: $(SRCS_DIR)/%.m | $(DEPS_DIR)
	@ echo "\t$(_YELLOW) compiling... $*.d$(RESET)"
	$(CC) $(FLAGS) -MM $< -MT $(@:.d=.o) -MF $@

all: init	$(NAME)

init:
	@ if test -f $(NAME); \
		then echo "$(CYAN)\t[program already created]$(RESET)";	\
		else \
		echo "$(_YELLOW)\t[Initialize program]$(RESET)"; \
		$(shell mkdir -p $(sort $(dir $(CPP_OBJS))) $(sort $(dir $(C_OBJS))) $(sort $(dir $(MM_OBJS))))	\
	fi

$(NAME):	$(C_OBJS) $(CPP_OBJS) $(MM_OBJS) $(M_OBJS)
	@echo "\t$(CYAN)[Creating program]$(RESET)"
	@echo "\t$(YELLOW) compiling$(_YELLOW)... $(RESET)$(YELLOW)$*.c++$*.cpp$*.mm$*.m$(RESET)"
	$(CXX) $(FLAGS) $(C_OBJS) $(CPP_OBJS) $(MM_OBJS) $(M_OBJS) -o $(NAME) $(LDFLAGS) $(LINKERFLAGS)
	@echo "$(CURSIVE)[Executable created & ready]$(RESET)\n\033[32mCompiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ"
	@echo "$(_GREEN)object files were in test$(RESET)"

clean:
	@echo "$(GRAY)[cleaning up .out & objects files]$(RESET)"
	rm -rf $(OBJS_DIR)

fclean:	clean
	@printf "$(RED)[cleaning up .out, objects & library files]$(_NC)\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"
	rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
