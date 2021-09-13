import * as React from 'react';
import { Alert, Button, StyleSheet, Image } from 'react-native';

import EditScreenInfo from '../components/EditScreenInfo';
import { Text, View } from '../components/Themed';
import { RootTabScreenProps } from '../types';

export default function TabOneScreen({ navigation }: RootTabScreenProps<'TabOne'>) {
  return (
    <View style={styles.container}>
      <View style={styles.titleContainer}>
        <Image
          style={styles.image}
          source={require('../assets/images/VA-logo.png')}
        />
      </View>
        <View style={styles.buttonContainer}>
          <Button
            title="Connect"
            color="white"
            onPress={() => Alert.alert('Simple Button pressed')}
          />
        </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container :{
    backgroundColor: '#ABD9FF',
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  title: {
    fontSize: 60,
    textAlign: 'center',
    color: 'white',
  },
  titleContainer: {
    marginTop: 10,
    backgroundColor: '#ABD9FF',
    marginBottom: 200,
  },
  button: {
    color: 'grey',
  },
  buttonContainer: {
    justifyContent: 'center',
    width: 300,
    height: 60,
    backgroundColor: 'grey',
    borderRadius: 30,
    color: 'white',
  },
  image: {
    width: 200,
    height: 200,
  }
});