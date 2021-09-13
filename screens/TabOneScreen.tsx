import * as React from 'react';
import { Alert, Button, StyleSheet } from 'react-native';

import EditScreenInfo from '../components/EditScreenInfo';
import { Text, View } from '../components/Themed';
import { RootTabScreenProps } from '../types';

export default function TabOneScreen({ navigation }: RootTabScreenProps<'TabOne'>) {
  return (
    <View style={styles.container}>
      <View style={styles.titleContainer}>
        <Text style={styles.title}>VAWARE</Text>
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
    backgroundColor: '#0078DC',
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  title: {
    fontSize: 60,
    textAlign: 'center',
  },
  titleContainer: {
    marginTop: 10,
    backgroundColor: 'white'
  },
  button: {
    color: 'grey',
  },
  buttonContainer: {
    width: '60%',
    backgroundColor: 'gray',
    backgroundColor: 'green',
    borderRadius: 15,
    color: 'white',
  }
});