ifndef   CDF_LIBRARY_PATH
  CDF_LIBRARY_PATH	= $(HOME)/usr/local/cdf36_4
endif

ifndef CLDIA_LIBRARY_PATH
CLDIA_LIBRARY_PATH	= $(HOME)/usr/local/cldia
endif

TARGET			= libCLDIA.a
INSTALL_PATH		= $(CLDIA_LIBRARY_PATH)

INCSDIR			= ./include
SRCSDIR			= ./srcs
DEPSDIR			= ./deps
OBJSDIR			= ./objs
INCSDIRS		= $(shell find $(INCSDIR) -type d)
SRCSDIRS		= $(shell find $(SRCSDIR) -type d)
DEPSDIRS		= $(patsubst $(SRCSDIR)%,$(DEPSDIR)%,$(SRCSDIRS))
OBJSDIRS		= $(patsubst $(SRCSDIR)%,$(OBJSDIR)%,$(SRCSDIRS))
INCS			= $(shell find $(INCSDIR) -name '*.h')
SRCS			= $(shell find $(SRCSDIR) -name '*.c')
DEPS			= $(patsubst $(SRCSDIR)/%.c,$(DEPSDIR)/%.d,$(SRCS))
OBJS			= $(patsubst $(SRCSDIR)/%.c,$(OBJSDIR)/%.o,$(SRCS))

MKDIR			= mkdir -p
RM			= rm -rf

AR			= ar rv
RANLIB			= ranlib
MAKE			= make --no-print-directory

CC			= gcc 
CC_INCLUDE		= $(patsubst %,-I%,$(INCSDIRS)) -I$(CDF_LIBRARY_PATH)/include

TEST_SRCSDIR		= ./test/srcs
TEST_BINDIR		= ./test/bin
TEST_OUTDIR		= ./test/out
TEST_SRCS		= $(shell find $(TEST_SRCSDIR) -name '*.c')
TEST_BIN		= $(patsubst $(TEST_SRCSDIR)/%.c,$(TEST_BINDIR)/%,$(TEST_SRCS))
TEST_OUT		= $(patsubst $(TEST_SRCSDIR)/%.c,$(TEST_OUTDIR)/%_o.txt,$(TEST_SRCS)) $(patsubst $(TEST_SRCSDIR)/%.c,$(TEST_OUTDIR)/%_e.txt,$(TEST_SRCS))

.PHONY			: all
all			: $(TARGET)

$(TARGET)		: $(DEPS) $(OBJS)
			@$(AR)    $@ $(OBJS)
			$(RANLIB) $@

$(DEPSDIR)/%.d		: $(SRCSDIR)/%.c 
			@$(MKDIR) $(patsubst %/,%,$(dir $@))
			$(CC) $(CC_INCLUDE) -I$(dir $<)include -MM -MP -MF $@ $<	

$(OBJSDIR)/%.o		: $(SRCSDIR)/%.c 
			@$(MKDIR) $(patsubst %/,%,$(dir $@))
			$(CC) $(CC_INCLUDE) -I$(dir $<)include          -o $@ $< -c

.PHONY			: build
build			: $(TARGET)

.PHONY			: clean
clean			: $(DEPSDIR) $(OBJSDIR) $(TARGET)
			$(RM) $(DEPSDIR) $(OBJSDIR) $(TARGET)

.PHONY			: install
install			: $(TARGET)
			$(MKDIR)           $(INSTALL_PATH)/include
			cp -r $(INCSDIR)/* $(INSTALL_PATH)/include/
			$(MKDIR)           $(INSTALL_PATH)/lib
			cp -r $(TARGET)    $(INSTALL_PATH)/lib 

.PHONY			: test
test			: $(TEST_BIN) $(TEST_OUT)

$(TEST_OUTDIR)/%_o.txt	: $(TEST_BINDIR)/%
			@$(MKDIR) $(TEST_OUTDIR)
			@./$< 1>$@ 2>$(patsubst %_o.txt,%_e.txt,$@)
			@echo 'TEST OK : $<'

$(TEST_OUTDIR)/%_e.txt	: $(TEST_BINDIR)/%
			@$(MKDIR) $(TEST_OUTDIR)
			@./$< 1>$(patsubst %_e.txt,%_o.txt,$@) 2>$@
			@echo 'TEST OK : $<'

$(TEST_BINDIR)/%	: $(TEST_SRCSDIR)/%.c $(TARGET)
			@$(MKDIR) $(TEST_BINDIR)
			@$(CC) $(CC_INCLUDE) -L./ -L$(CDF_LIBRARY_PATH)/lib -o $@ $< -l$(patsubst lib%.a,%,$(TARGET)) -lcdf -lz

.PHONY			: testclean
testclean		: $(TEST_BINDIR) $(TEST_OUTDIR)
			$(RM) $(TEST_BINDIR) $(TEST_OUTDIR)

ifneq ($(filter     clean,$(MAKECMDGOALS)),    clean)
ifneq ($(filter testclean,$(MAKECMDGOALS)),testclean)
-include $(DEPS)
endif
endif
