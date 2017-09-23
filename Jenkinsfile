pipeline {
    agent any
    stages {
        stage('Build')
        {
            steps {
                sh 'make'
                archiveArtifacts artifacts: 'strace', fingerprint: true
            }
        }
    }
}
