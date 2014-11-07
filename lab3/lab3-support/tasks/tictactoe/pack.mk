PROGS_TYPO_OBJS := tictactoe.o
PROGS_TYPO_OBJS := $(PROGS_TYPO_OBJS:%=$(TDIR)/tictactoe/%)
ALL_OBJS += $(PROGS_TYPO_OBJS)

$(TDIR)/bin/tictactoe : $(TSTART) $(PROGS_TYPO_OBJS) $(TLIBC)

