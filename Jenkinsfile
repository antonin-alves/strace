pipeline {
    agent {
        docker { image "ubuntu:latest" }
    }
    stages {
        stage('Build')
        {
            steps {
                sh 'echo "Yolooooooooooooooooooooooooooooooooo !"'
                sh 'make'
                archiveArtifacts artifacts: 'strace', fingerprint: true
            }
        }
    }
}
