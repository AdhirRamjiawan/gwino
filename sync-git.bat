IF [%1] == [] (
    echo Comment missing
    exit /b
) 


IF [%2] == [] (
    echo branch name missing
    exit /b
) 

git status
git pull origin %2
git add *
git commit -m %1
git push origin %2