# GitMaster
A simple C util for Git. Quickly search for and checkout remote branches along with additional listed features. Installation is simple. Compile binary files and move into your /usr/local/bin (on a mac). Give the binary proper permissions and you're good to go.

## Common use: 
gitmaster <name of branch>: This will query all branches in the repo and return a list of available branches to checkout. \
### Operators: 
**-a**: Amend existing commit on current branch. \
**-ap**: Amend latest commit with current changes, and pushes to remote branch. \
**-apply**: Applies selected patch as a commit with same name as patch description. \
**-c**: Creates a new commit with current changes, and entered description and pushes to remote branch. \
**-commit**: Creates commit from current changes with provided description. \
**-rs**: Resets branch head by nth amount, and stashes changes with description text entered. \
**-rebase**: Allows user to reset branch head and rebase to remote or local branches. \
**-stash**: Creates stash with provided name of current changes. 
